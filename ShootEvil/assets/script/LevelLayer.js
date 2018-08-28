// Learn cc.Class:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/class.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/class.html
// Learn Attribute:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/reference/attributes.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/reference/attributes.html
// Learn life-cycle callbacks:
//  - [Chinese] http://docs.cocos.com/creator/manual/zh/scripting/life-cycle-callbacks.html
//  - [English] http://www.cocos2d-x.org/docs/creator/en/scripting/life-cycle-callbacks.html

cc.Class({
  extends: cc.Component,

  properties: {
    itemPrefab: {
      default: null,
      type: cc.Prefab
    }
  },

  // LIFE-CYCLE CALLBACKS:
  init(level) {
    this.level = this.getCountNumber(level);
    this.itemPool = new cc.NodePool("Item");
    let initCount = this.level;
    for (let i = 0; i < initCount; ++i) {
      let item = cc.instantiate(this.itemPrefab); // 创建节点
      item.setPosition(-450+i%4*300,200-Math.floor(i/4)*300);
      this.node.addChild(item);
    }
    console.log(this);
  },

  getCountNumber(level) {
    if (level === 1) {
      return 8;
    } else {
      return 10;
    }
  },

  onLoad() {
    // this.node.active = true;
  },

  start() {}

  // update (dt) {},
});
