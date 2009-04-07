/*
 * OpenPaint
 * www.sourceforge.net/projects/openpaint
 *
 * Copyright (C) 2007, Steven Jedlicka
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */	


#include "ConfigFile.h"

//Make sure this is set in project settings: TIXML_USE_STL
#include "tinyxml.h"

ConfigFile::ConfigFile()
{
    m_bOpenSuccessful = false;
    bIsModified = false;
}

ConfigFile::ConfigFile(std::string identifier)
{
    m_bOpenSuccessful = false;
    bIsModified = false;
    m_strIdentifier = identifier;
}

ConfigFile::ConfigFile(std::string filename, std::string identifier, bool bAddDefaultsToConfig)
{
    m_strFilename = filename;
    m_strIdentifier = identifier;
    m_bAddDefaultsToConfig = bAddDefaultsToConfig;
    m_bOpenSuccessful = false;
    bIsModified = false;

    //Add default configurations
    LoadDefaults();
    
    m_bOpenSuccessful = ReadConfigFile();
    if(!m_bOpenSuccessful)
    {
        std::cout << "Failed to read config file. Using defaults." << std::endl;
    }
    
}

ConfigFile::~ConfigFile(){}

void ConfigFile::LoadDefaults()
{
    //Virtual function needs to be overloaded to set the default configurations
}

bool ConfigFile::IsOpen()
{
    return m_bOpenSuccessful;
}

bool ConfigFile::Save()
{
    bool bSuccess = WriteConfigFile();

    if(bSuccess)
    {
        m_bOpenSuccessful = true;
        bIsModified = false;
    }

    return bSuccess;
}


//Save the file to the new filename and switch all preceding saves to that file
bool ConfigFile::SaveAs(std::string filename)
{
    std::string strTempFilename = m_strFilename;
    m_strFilename = filename;
    if(WriteConfigFile() == 0)
    {
        //Saveas failed so revert to old filename
        m_strFilename = strTempFilename;
        return false;
    }
    m_bOpenSuccessful = true;
    bIsModified = false;
    return true;
}

bool ConfigFile::IsModified()
{
    return bIsModified;
}

std::string ConfigFile::LastError()
{
    return m_strLastError;
}


bool ConfigFile::ReadConfigFile()
{
    TiXmlDocument doc( m_strFilename.c_str() );
     
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
		std::cout << "Could not load test file '"<< m_strFilename <<"'. Error='" << doc.ErrorDesc() << "'. Using Default Data"  << std::endl;
        m_strLastError = doc.ErrorDesc();
        //Use already loaded defaults
		return false;
	}
	
	TiXmlNode* parent = 0;
    TiXmlNode* child = 0;
    TiXmlNode* tempChild = 0;
	TiXmlElement* configElement = 0;
	TiXmlElement* itemElement = 0;
    TiXmlElement* tempElement = 0;

	// Get the "configData" element.
    parent = doc.FirstChild( m_strIdentifier.c_str() );
	assert( parent  );
	configElement =parent->ToElement();
	assert( configElement  );	

	//Read all the configuration data
    for( child = configElement->FirstChild(); child; child = child->NextSibling() )
    {
        itemElement = child->ToElement();
	    assert( itemElement  );
        
        //convert to uppercase
        std::string strElement = itemElement->Value();

        //replace underscore with whitespace
        std::replace(strElement.begin(), strElement.end(), '_', ' ');

        ConfigAttribute element;
        element.strAttribute = strElement;
        element.strValue = itemElement->Attribute( "value");
        
        //Read the sub items from the file and store as an array
        if(!itemElement->NoChildren() || element.strValue == "Array()")
        {
            element.bIsArray = true;

            for( tempChild = itemElement->FirstChild(); tempChild; tempChild = tempChild->NextSibling() )
            {
                tempElement = tempChild->ToElement();
                assert( tempElement  );

                element.listValues.push_back(tempElement->Attribute( "value"));
            }

        }
        m_mapConfig[Uppercase(strElement)] = element;
    }

    return true;
    
}

bool ConfigFile::ImportXML(std::string strXML)
{
    TiXmlDocument doc;
    
    //Load document from strXML using streams
    std::istringstream strIStream;
    strIStream.str(strXML);
    strIStream >> doc;
    
    if ( doc.NoChildren() )
	{
		std::cout << "Could not parse xml string. Error='" << doc.ErrorDesc() << "'. Using Default Data"  << std::endl;
        m_strLastError = doc.ErrorDesc();
        //Use already loaded defaults
		return false;
	}

    TiXmlNode* parent = 0;
    TiXmlNode* child = 0;
    TiXmlNode* tempChild = 0;
	TiXmlElement* configElement = 0;
	TiXmlElement* itemElement = 0;
    TiXmlElement* tempElement = 0;

	// Get the "configData" element.
    parent = doc.FirstChild( m_strIdentifier.c_str() );
	assert( parent  );
	configElement =parent->ToElement();
	assert( configElement  );	

	//Read all the configuration data
    for( child = configElement->FirstChild(); child; child = child->NextSibling() )
    {
        itemElement = child->ToElement();
	    assert( itemElement  );
        
        //convert to uppercase
        std::string strElement = itemElement->Value();

        //replace underscore with whitespace
        std::replace(strElement.begin(), strElement.end(), '_', ' ');

        ConfigAttribute element;
        element.strAttribute = strElement;
        element.strValue = itemElement->Attribute( "value");
        
        //Read the sub items from the file and store as an array
        if(!itemElement->NoChildren() || element.strValue == "Array()")
        {
            element.bIsArray = true;

            for( tempChild = itemElement->FirstChild(); tempChild; tempChild = tempChild->NextSibling() )
            {
                tempElement = tempChild->ToElement();
                assert( tempElement  );

                element.listValues.push_back(tempElement->Attribute( "value"));
            }

        }
        m_mapConfig[Uppercase(strElement)] = element;
    }

    return true;

    return true;
}

bool ConfigFile::WriteConfigFile()
{
    TiXmlDocument doc( m_strFilename.c_str() );

    TiXmlElement configData( m_strIdentifier.c_str() );
    configData.SetAttribute( "version", "1.0");

    //Loop through all the configurations
    std::map<std::string, ConfigAttribute>::iterator configIter;
    for(configIter = m_mapConfig.begin(); configIter != m_mapConfig.end(); configIter++)
    {
        ConfigAttribute item = configIter->second;
        std::string firstItem = item.strAttribute;

        //replace whitespace with underscore
        std::replace(firstItem.begin(), firstItem.end(), ' ', '_');
        TiXmlElement elementConfigItem (firstItem.c_str() );
        elementConfigItem.SetAttribute( "value", item.strValue.c_str());

        //Add array sub items to the xml
        if(item.bIsArray)
        {
            for(std::vector<std::string>::iterator iter = item.listValues.begin(); iter != item.listValues.end(); iter++)
            {
                std::string strTemp = *iter;
                TiXmlElement elementArrayItem (firstItem.c_str() );
                elementArrayItem.SetAttribute( "value", strTemp.c_str());
                elementConfigItem.LinkEndChild(elementArrayItem.Clone());
            }
        }
        configData.LinkEndChild(elementConfigItem.Clone());
    }
	doc.LinkEndChild(configData.Clone());

	//Save the config file
	return doc.SaveFile();
}

std::string ConfigFile::ExportXML()
{
    TiXmlDocument doc( m_strFilename.c_str() );

    TiXmlElement configData( m_strIdentifier.c_str() );
    configData.SetAttribute( "version", "1.0");

    //Loop through all the configurations
    std::map<std::string, ConfigAttribute>::iterator configIter;
    for(configIter = m_mapConfig.begin(); configIter != m_mapConfig.end(); configIter++)
    {
        ConfigAttribute item = configIter->second;
        std::string firstItem = item.strAttribute;

        //replace whitespace with underscore
        std::replace(firstItem.begin(), firstItem.end(), ' ', '_');
        TiXmlElement elementConfigItem (firstItem.c_str() );
        elementConfigItem.SetAttribute( "value", item.strValue.c_str());

        //Add array sub items to the xml
        if(item.bIsArray)
        {
            for(std::vector<std::string>::iterator iter = item.listValues.begin(); iter != item.listValues.end(); iter++)
            {
                std::string strTemp = *iter;
                TiXmlElement elementArrayItem (firstItem.c_str() );
                elementArrayItem.SetAttribute( "value", strTemp.c_str());
                elementConfigItem.LinkEndChild(elementArrayItem.Clone());
            }
        }
        configData.LinkEndChild(elementConfigItem.Clone());
    }
	doc.LinkEndChild(configData.Clone());

    std::string strReturnXML;
    std::ostringstream strStream;
    
    strStream << doc;
    strReturnXML = strStream.str();
    
	//Save the config file
	return strReturnXML;
}

std::string ConfigFile::getString(std::string strAttribute, std::string strDefault)
{
    std::map<std::string, ConfigAttribute>::iterator p;
    
    //Find the uppercase string in the map
    std::string lstr = Uppercase(strAttribute);
    p = m_mapConfig.find(lstr);
    
    if (p != m_mapConfig.end())
    {
        return p->second.strValue;
    }
    else
    {
        std::cout << "Variable " << strAttribute.c_str() << " does not exist in config file." <<  std::endl;

        //Store the default value in the config file
        if(m_bAddDefaultsToConfig)
        {
            setString(strAttribute, strDefault);
        }
        return strDefault;
    }
 }
 
 double ConfigFile::getDouble(std::string strAttribute, double dDefault)
{
    std::string strDefault;
    std::ostringstream strStream;
    
    strStream << dDefault;
    strDefault = strStream.str();

    return atof(getString(strAttribute, strDefault).c_str());
}

int ConfigFile::getInteger(std::string strAttribute, int iDefault)
{
    std::string strDefault;
    std::ostringstream strStream;
    
    strStream << iDefault;
    strDefault = strStream.str();
    
    return atoi(getString(strAttribute, strDefault).c_str());
}

bool ConfigFile::getBool(std::string strAttribute, bool bDefault)
{
    std::string strReturn;
    std::string strDefault;
    std::ostringstream strStream;
    
    strStream << bDefault;
    strDefault = strStream.str();
    
    strReturn = getString(strAttribute, strDefault);
    if(strReturn == "1" || Uppercase(strReturn) == "TRUE")
    {
        return true;
    }
    return false;
}

std::vector<std::string> ConfigFile::getArray(std::string strAttribute, std::vector<std::string> listDefaults)
{
    std::map<std::string, ConfigAttribute>::iterator p;
    
    //Find the uppercase string in the map
    std::string lstr = Uppercase(strAttribute);
    p = m_mapConfig.find(lstr);
    
    if (p != m_mapConfig.end() && p->second.bIsArray)
    {
        return p->second.listValues;
    }
    else
    {
        std::cout << "Variable " << strAttribute.c_str() << " does not exist in config file or is not an array." <<  std::endl;
        
        //Store the default value in the config file
        if(m_bAddDefaultsToConfig && listDefaults.size() > 0)
        {
            setArray(strAttribute, listDefaults);
        }

        return listDefaults;
    }
}

std::vector<std::string> ConfigFile::getAttributeList()
{
    std::vector<std::string> returnList;

    std::map<std::string, ConfigAttribute>::iterator iter = m_mapConfig.begin();
    for(iter = m_mapConfig.begin(); iter != m_mapConfig.end(); iter++)
    {
        returnList.push_back(iter->second.strAttribute.c_str());
    }

    return returnList;
}

std::vector<std::string> ConfigFile::getValueList()
{
    std::vector<std::string> returnList;

    std::map<std::string, ConfigAttribute>::iterator iter = m_mapConfig.begin();
    for(iter = m_mapConfig.begin(); iter != m_mapConfig.end(); iter++)
    {
        returnList.push_back(iter->second.strValue);
    }
    
    return returnList;
}

void ConfigFile::setString(std::string strAttribute, std::string strValue)
{
    ConfigAttribute element;
    element.strAttribute = strAttribute;
    element.strValue = strValue;
    m_mapConfig[Uppercase(strAttribute)] = element;
    bIsModified = true;
}

void ConfigFile::setDouble(std::string strAttribute, double dValue)
{
    std::string strDefault;
    std::ostringstream strStream;
    
    strStream << dValue;
    strDefault = strStream.str();

    setString(strAttribute, strDefault);
}

void ConfigFile::setInteger(std::string strAttribute, int iValue)
{
    std::string strDefault;
    std::ostringstream strStream;
    
    strStream << iValue;
    strDefault = strStream.str();
    
    setString(strAttribute, strDefault);
}

void ConfigFile::setBool(std::string strAttribute, bool bValue)
{
    std::string strDefault;
    std::ostringstream strStream;
    
    strStream << bValue;
    strDefault = strStream.str();
    
    setString(strAttribute, strDefault);
}

void ConfigFile::setArray(std::string strAttribute, std::vector<std::string> listValues)
{
    //Put the string in the map
    setString(strAttribute, "Array()");

    //Get the ConfigAttribute out of the map
    std::map<std::string, ConfigAttribute>::iterator p;
    
    //Find the uppercase string in the map
    std::string lstr = Uppercase(strAttribute);
    p = m_mapConfig.find(lstr);
    
    if (p != m_mapConfig.end())
    {
        p->second.bIsArray = true;
        p->second.listValues = listValues;
    }
    
}

std::string ConfigFile::Uppercase(std::string strInput)
{
    std::transform(strInput.begin(), strInput.end(), strInput.begin(), toupper);
    return strInput;
}

void ConfigFile::DumpConfig()
{
    std::map<std::string, ConfigAttribute>::iterator iter = m_mapConfig.begin();
    
    int i = 1;
    for(iter = m_mapConfig.begin(); iter != m_mapConfig.end(); iter++)
    {
        printf("%d: key= %s  element= %s = %s\n", i, iter->first.c_str(), iter->second.strAttribute.c_str(), iter->second.strValue.c_str() );
        i++;
    }
    
}

#ifdef CONFIG_DEBUG

#include <iostream>

int main(int argc, char *argv[])
{
    int iThreadId;
    printf("Starting %s\n", argv[0]);
    if(argc < 1)
    {
        return 0;
    }
    
    CConfigManager* config = CConfigManager::Instance();
    config->DumpConfigToLog();
    
    printf("Variable: %s" config->getString("Variable", "123"));
    printf("Setting: %s" config->getString("Setting", "data"));
}

#endif
