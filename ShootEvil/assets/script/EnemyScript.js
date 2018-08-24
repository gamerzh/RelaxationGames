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

  properties: {},

  // LIFE-CYCLE CALLBACKS:

  onLoad() {},

  start() {
    
  },

  init(gameScript){
    this.blood = 5;
  },

  // 只在两个碰撞体开始接触时被调用一次
  onBeginContact: function(contact, selfCollider, otherCollider) {
    console.log("ball onBeginContact");
    console.log(otherCollider);
    if (otherCollider.node.name == "bullet") {
      this.blood -= 1;
    }else if(otherCollider.node.name == "ground"){
      console.log("KKKKKKKKKK");
    }
  },

  // 只在两个碰撞体结束接触时被调用一次
  onEndContact: function(contact, selfCollider, otherCollider) {
    console.log("ball onEndContact");
  },

  // 每次将要处理碰撞体接触逻辑时被调用
  onPreSolve: function(contact, selfCollider, otherCollider) {
    // console.log("onPreSolve onPreSolve onPreSolve");
  },

  // 每次处理完碰撞体接触逻辑时被调用
  onPostSolve: function(contact, selfCollider, otherCollider) {
    // console.log("onPostSolve onPostSolve on  PostSolve");
  },

  update(dt) {
    if (this.blood <= 0) {
      this.node.removeFromParent();
    }
  }
});
