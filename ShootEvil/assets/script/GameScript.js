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
    bulletPrefab: {
      default: null,
      type: cc.Prefab
    },
    enemyPrefab: {
      default: null,
      type: cc.Prefab
    },
    hero: {
      default: null,
      type: cc.Node
    }
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

    // var collisionManager = cc.director.getCollisionManager();
    // collisionManager.enabled = true;
    // collisionManager.enabledDebugDraw = true;
    this.touchEvent();
  },

  start() {
    this.initBulletPool();
    this.initEnemyPool();
    this.schedule(function() {
      this.generateEnemy();
    }, 5);
  },

  initBulletPool() {
    this.bulletPool = new cc.NodePool("Bullet");
    let initCount = 20;
    for (let i = 0; i < initCount; ++i) {
      let bullet = cc.instantiate(this.bulletPrefab); // 创建节点
      this.bulletPool.put(bullet); // 通过 putInPool 接口放入对象池
    }
  },

  initEnemyPool() {
    this.enemyPool = new cc.NodePool("Enemy");
    let initCount = 10;
    for (let i = 0; i < initCount; ++i) {
      let enemy = cc.instantiate(this.enemyPrefab); // 创建节点
      this.enemyPool.put(enemy); // 通过 putInPool 接口放入对象池
    }
  },

  generateBullet(pos) {
    let bullet = null;
    if (this.bulletPool.size() > 0) {
      // 通过 size 接口判断对象池中是否有空闲的对象
      bullet = this.bulletPool.get();
    } else {
      // 如果没有空闲对象，也就是对象池中备用对象不够时，我们就用 cc.instantiate 重新创建
      bullet = cc.instantiate(this.bulletPrefab);
    }
    // console.log("AAAAAA = "+pos.x);
    bullet.setPosition(pos.x, pos.y);
    // this.node.addChild(bullet);
    var scene = cc.director.getScene();
    bullet.parent = scene;
    console.log(this);
    bullet.getComponent("BulletScript").init(this); //接下来就可以调用 bullet 身上的脚本进行初始化
  },

  recycleBullet: function(bullet) {
    this.bulletPool.put(bullet);
  },

  generateEnemy() {
    let enemy = null;
    if (this.enemyPool.size() > 0) {
      // 通过 size 接口判断对象池中是否有空闲的对象
      enemy = this.enemyPool.get();
    } else {
      // 如果没有空闲对象，也就是对象池中备用对象不够时，我们就用 cc.instantiate 重新创建
      enemy = cc.instantiate(this.enemyPrefab);
    }
    enemy.setPosition(Math.random() * 1280, 680);
    var scene = cc.director.getScene();
    enemy.parent = scene;
    console.log(this);
    enemy.getComponent("EnemyScript").init(this); //接下来就可以调用 bullet 身上的脚本进行初始化
  },

  recycleEnemy: function(enemy) {
    this.enemyPool.put(enemy);
  },

  shoot() {
    // console.log("HAHAHA"+this.hero.x);
    this.generateBullet(cc.v2(this.hero.x, this.hero.y));
  },

  update(dt) {
    if (this.moveLeft) {
      this.hero.x -= 2;
    } else if (this.moveRight) {
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
        if (temp.x <= 200) {
          this.moveLeft = true;
        } else if (temp.x <= 400) {
          this.moveRight = true;
        } else if (temp.x >= 880 && temp.x < 1080) {
          //TODO:
        } else if (temp.x > 1080) {
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
  }
});
