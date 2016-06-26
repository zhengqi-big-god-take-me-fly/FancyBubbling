#include "GameSceneModel.h"

bool GameSceneModel::init() {
    // TODO
    this->_status = Status::ready;
    return true;
}

// 获取地图大小
// 返回值 pair(column, row)
Size GameSceneModel::getMapSize() {
    unsigned int row = map.size();
    unsigned int column = row > 0 ? map[0].size() : 0;
    return Size(column, row);
}
// 删除地图中的指定元素
bool GameSceneModel::removeMap(unsigned int column, unsigned int row) {
    if (row < map.size() && column < map[row].size()) {
        map[row].replace(column, BlockModel::create("empty"));
        return true;
    }
    return false;
}
// 设置地图中的指定元素
bool GameSceneModel::setMap(unsigned int column, unsigned int row, BlockModel * block) {
    if (row < map.size() && column < map[row].size()) {
        block->setPosition(Vec2(column, row));
        map[row].replace(column, block);
        return true;
    }
    return false;
}
// 获取地图指定元素
BlockModel * GameSceneModel::getMap(unsigned int column, unsigned int row) {
    if (row < map.size() && column < map[row].size()) {
        return map[row].at(column);
    }
    return nullptr;
}

bool GameSceneModel::readConfigFromFile(const std::string & fileName) {
    std::ifstream file(FileUtils::getInstance()->fullPathForFilename(fileName));
    if (!file) return false;
    std::string str;
    
    // read whole file to str
    
    file.seekg(0, std::ios::end);
    str.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    
    str.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    // parse JSON
    
    rapidjson::Document d;
    if (d.HasParseError()) return false;
    d.Parse(str.c_str());
    rapidjson::Value& data = d["data"];
    if (!data.IsObject()) return false;
    
    // read blocks
    rapidjson::Value& blocks = data["blocks"];
    std::map<int, std::string> id_to_key;
    if (!blocks.IsArray()) return false;
    for (int i = 0; i < blocks.Size(); ++i) {
        rapidjson::Value& block = blocks[i];
        if (!block.IsObject()) return false;
        
        auto b = BlockModel::create();
        
        int block_id = block["id"].GetInt();
        std::string block_key = block["key"].GetString();
        id_to_key[block_id] = block_key;
        
        // texutre
        if (block.HasMember("texture") && block["texture"].IsString())
            b->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(block["texture"].GetString()));
        // breakable
        if (block.HasMember("breakable") && block["breakable"].IsBool()) {
            b->setBreakable(block["breakable"].GetBool());
        }
        // blockwave
        if (block.HasMember("blockWave") && block["blockWave"].IsBool()) {
            b->setBlockWave(block["blockWave"].GetBool());
        }
        
        BlockModel::registerBlock(b, block_key);
    }
    
    // read map
    rapidjson::Value& map_size = data["map_size"];
    if (!map_size.IsObject() || !map_size.HasMember("column") || !map_size["column"].IsInt() || !map_size.HasMember("row") || !map_size["row"].IsInt()) return false;
    int column = map_size["column"].GetInt(), row = map_size["row"].GetInt();
    
    //        auto mapSize = getMapSize();
    
    //        CCLOG("%f %f", mapSize.width, mapSize.height);
    
    rapidjson::Value& map = data["map"];
    if (!map.IsArray()) return false;
    this->map.resize(row);
    for (int x = 0; x < column; ++x) {
        for (int y = 0; y < row; ++y) {
            int index = y + x * row;
            if (map.Size() <= index) return false;
            int block_id = map[index].GetInt();
            std::string block_key = id_to_key[block_id];
            //              setMap(x, y, BlockModel::create(block_key));
            this->map[y].pushBack(BlockModel::create(block_key));
        }
    }
    
    return true;
}
