#include "BlockModel.h"

std::map<std::string, BlockModel> BlockModel::_registPool;

bool BlockModel::init() {
    return true;
}

bool BlockModel::registerBlock(BlockModel * block, const std::string & key) {
    if (!block || _registPool.find(key) != _registPool.end()) {
        return false;
    }
    block->_key = key;
    _registPool[key] = *block;
    return true;
}

BlockModel * BlockModel::create(const std::string & key) {
    auto it = _registPool.find(key);
    if (it != _registPool.end()) {
        BlockModel * pRet = new BlockModel(it->second);
        if (pRet) {
            pRet->autorelease();
            return pRet;
        }
    }
    return nullptr;
}

bool BlockModel::isBreakable() const {
    return _breakable;
}

bool BlockModel::isBlockWave() const {
    return _blockWave;
}