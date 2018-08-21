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

  },

  // LIFE-CYCLE CALLBACKS:

  onLoad () {},

  start() {},

  init() {},

  update(dt) {
    var pos = this.node.getPosition();
    this.node.setPosition(pos.x, pos.y + 4);
  },

  // 只在两个碰撞体开始接触时被调用一次
  onBeginContact: function(contact, selfCollider, otherCollider) {
    console.log("onBeginContact onBeginContact onBeginContact");
    // Game.recycleBullet(this);
  },

  // 只在两个碰撞体结束接触时被调用一次
  onEndContact: function(contact, selfCollider, otherCollider) {
    console.log("onEndContact onEndContact onEndContact");
  },

  // 每次将要处理碰撞体接触逻辑时被调用
  onPreSolve: function(contact, selfCollider, otherCollider) {
    // console.log("onPreSolve onPreSolve onPreSolve");
  },

  // 每次处理完碰撞体接触逻辑时被调用
  onPostSolve: function(contact, selfCollider, otherCollider) {
    // console.log("onPostSolve onPostSolve onPostSolve");
  }

});
