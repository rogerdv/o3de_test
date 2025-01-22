#include <AzCore/std/string/string.h>
#include <AzCore/IO/FileIO.h>
#include <AzCore/Serialization/SerializeContext.h>

#include "BaseItem.h"
#include "ItemArmor.h"
#include "ItemWeapon.h"

namespace keyw {
    /*class Item {
    public:
        int id;
        AZStd::string name;
        AZStd::string type;
        AZStd::string rarity;
    };*/

    class ItemLoader
    {
    public:
        AZStd::vector<BaseItem> LoadItems(const AZStd::string& filePath)
        {
            AZStd::vector<BaseItem> items;

            // load JSON file
            AZ::IO::FileIOStream stream(filePath.c_str(), AZ::IO::OpenMode::ModeRead);
            if (!stream.IsOpen())
            {
                AZ_Error("ItemLoader", false, "Failed to open file: %s", filePath.c_str());
                return items;
            }

            AZStd::string jsonText;
            jsonText.resize(stream.GetLength());
            stream.Read(jsonText.size(), jsonText.data());

            rapidjson::Document document;
            if (document.Parse(jsonText.c_str()).HasParseError())
            {
                AZ_Error("ItemLoader", false, "Failed to parse JSON file.");
                return items;
            }

            // Iterate over Json items
            for (const auto& itemValue : document.GetArray())
            {
                BaseItem item;
                ItemWeapon w;
                AZStd::string t;
                t=itemValue["category"].GetString();
                if (t == "weapon") {
                    ParseCommon(itemValue, w);
                    ParseWeaponItem(itemValue, w);
                    items.push_back(w);
                }
                else {
                    ParseCommon(itemValue, item);
                    items.push_back(item);
                }
                
            }

            return items;
        }


        void ParseWeaponItem(const rapidjson_ly::Value & itemValue, ItemWeapon &it) {
            if (itemValue.HasMember("damage"))
            {
                int i = 0;
                for (auto& v: itemValue["damage"].GetArray()) {
                    it.Dmg[i] = v.GetFloat();
                }

            }
            it.Dmg = { 10,1,1,1,0 };
        }
        
        // PArse values common to all items
        void ParseCommon(const rapidjson_ly::Value& itemValue, BaseItem& item) {
            item.Id = itemValue["id"].GetString();
            item.Category = itemValue["category"].GetString();
            item.ItemType = itemValue["type"].GetString();
            if (itemValue.HasMember("asset"))
            {
                item.PrefabAsset = itemValue["asset"].GetString();
            }
            if (itemValue.HasMember("weight"))
            {
                item.Weight = itemValue["weight"].GetInt();
            }
            if (itemValue.HasMember("equip_event")) {
                item.TestSc = itemValue["equip_event"].GetString();
            }
            item.Rarity = itemValue["rarity"].GetFloat();
        }
    };

    
}