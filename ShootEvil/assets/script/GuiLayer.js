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
        levelLayer:cc.Node,
    },

    // LIFE-CYCLE CALLBACKS:

    // onLoad () {},

    start () {

    },

    // update (dt) {},

    selectLevelOne: function (event) {
        //这里的 event 是一个 EventCustom 对象，你可以通过 event.detail 获取 Button 组件
        var button = event.detail;
        //do whatever you want with button
        //另外，注意这种方式注册的事件，也无法传递 customEventData
        console.log("select level one");
        this.levelLayer.active = true;
        this.levelLayer.getComponent("LevelLayer").init(1);
     },

     selectLevelTwo:function (event){
        console.log("select level two");
     },

     selectLevelThree:function (event){
        console.log("select level three");
    }
});
