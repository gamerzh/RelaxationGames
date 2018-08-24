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
        progressBar:cc.ProgressBar
    },

    // LIFE-CYCLE CALLBACKS:

    onLoad () {
        cc.director.preloadScene("MainScene", function () {
            cc.log("Next scene preloaded");
        });
       this.progressBar.progress = 0;
    },

    start () {
        this.schedule(function() {
            this.progressUp();
          },0.1);
    },

    progressUp(){
        if(this.progressBar.progress<1){
            this.progressBar.progress += 0.05;
        }else{
            cc.director.loadScene("MainScene");
        }
    },

    // update (dt) {},
});
