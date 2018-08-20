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
    hero: cc.Node
  },

  // LIFE-CYCLE CALLBACKS:

  onLoad() {
    var physicsManager = cc.director.getPhysicsManager();
    physicsManager.enabled = true;
    physicsManager.debugDrawFlags =
      cc.PhysicsManager.DrawBits.e_aabbBit |
      cc.PhysicsManager.DrawBits.e_pairBit |
      cc.PhysicsManager.DrawBits.e_centerOfMassBit |
      cc.PhysicsManager.DrawBits.e_jointBit |
      cc.PhysicsManager.DrawBits.e_shapeBit;

    var collisionManager = cc.director.getCollisionManager();
    collisionManager.enabled = true;
    collisionManager.enabledDebugDraw = true;
    this.touchEvent();
  },

  start() {
    //TODO:
  },

  update(dt) {
    if (this.moveLeft) {
      this.hero.x -= 2;
    }else if(this.moveRight){
      this.hero.x += 2;
    }
  },

  touchEvent() {
    // 使用枚举类型来注册
    this.node.on(
      cc.Node.EventType.TOUCH_START,
      function(event) {
        console.log("Touch down");
        var temp = event.getLocation();
        if(temp.x<=200){
          this.moveLeft = true;
        }else if(temp.x<=400){
          this.moveRight = true;
        }else if(temp.x>=880 && temp.x<1080){
          //TODO:
        }else if(temp.x>1080){
            this.shoot();
        }
        console.log("x = ", temp.x);
        console.log("y = ", temp.y);
      },
      this
    );
    this.node.on(
      cc.Node.EventType.TOUCH_END,
      function(event) {
        this.moveLeft = false;
        this.moveRight = false;
      },
      this
    );
    // this.node.on(
    //   cc.Node.EventType.MOUSE_DOWN,
    //   function(event) {
    //     console.log("Mouse down ...");
    //   },
    //   this
    // );
    // this.node.on(
    //   cc.Node.EventType.MOUSE_UP,
    //   function(event) {
    //     console.log("Mouse down ...");
    //     this.moveLeft = false;
    //   },
    //   this
    // );
  },

  shoot(){


  },

});
