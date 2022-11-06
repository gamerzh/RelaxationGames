
package com.hifreshday.android.setting;

import com.hifreshday.android.setting.persistence.SettingsPreferences;

import android.content.Context;


/**
 * 设置接口的实现类
 * 
 * @author bluestome.zhang
 */
public class SettingImpl implements Setting {

    private Context ctx = null;
    private SettingsPreferences settingPreferences = null;
    private static Setting instance = null;
    boolean isBind = false;

    private SettingImpl(Context ctx) {
        this.ctx = ctx;
        this.settingPreferences = new SettingsPreferences(ctx);
    }

    public static Setting getInstance(Context ctx) {
        if (null == instance) {
            instance = new SettingImpl(ctx);
        }
        return instance;
    }

    /**
     * 背景音乐调节
     * 
     * @param value 背景音乐值
     */
    @Override
    public synchronized boolean adjustBGVoice(Integer value) {
        return settingPreferences.saveData(Setting.BGVOICE, value);
    }

    /**
     * 获取背景音量
     * 
     * @return Integer
     */
    @Override
    public Integer getBGVoice() {
        return (Integer) settingPreferences.getData(Setting.BGVOICE, 0);
    }

    /**
     * 游戏音效调节
     * 
     * @param value 游戏音效值
     */
    @Override
    public synchronized boolean adjustGameMusic(Integer value) {
        return settingPreferences.saveData(Setting.GAMEVOICE, value);
    }

    /**
     * 获取游戏音量
     * 
     * @return Integer
     */
    @Override
    public Integer getGameMusic() {
        return (Integer) settingPreferences.getData(Setting.GAMEVOICE, 0);
    }

    /**
     * 亮度调节
     * 
     * @param value 亮度值
     */
    @Override
    public synchronized boolean adjustBrightness(Integer value) {
        return settingPreferences.saveData(Setting.BRIGHTNESS, value);
    }

    /**
     * 获取亮度值
     * 
     * @return Integer
     */
    @Override
    public Integer getBrightness() {
        return (Integer) settingPreferences.getData(Setting.BRIGHTNESS, 0);
    }

    /**
     * 震动开关调节
     * 
     * @param value 是否开启震动
     */
    @Override
    public synchronized boolean shockSwitch(Boolean value) {
        return settingPreferences.saveData(Setting.SHOCK, value);
    }

    /**
     * 获取震动开关设置
     * 
     * @return Boolean
     */
    @Override
    public Boolean getShockValue() {
        return (Boolean) settingPreferences.getData(Setting.SHOCK, true);
    }

    /**
     * 动画开关调节
     * 
     * @param value 是否开启动画
     */
    @Override
    public synchronized boolean animationSwitch(Boolean value) {
        return settingPreferences.saveData(Setting.ANIMATION, value);
    }

    /**
     * 获取动画开关设置
     * 
     * @return Boolean
     */
    @Override
    public Boolean getAnimationValue() {
        return (Boolean) settingPreferences.getData(Setting.ANIMATION, true);
    }

    /**
     * 设置其他参数
     * 
     * @param name 键名
     * @param value 值
     */
    @Override
    public synchronized boolean setOtherProperties(String name, Object value) {
        return settingPreferences.saveData(name, value);
    }

    /**
     * 根据参数名获取参数
     * 
     * @param key 键名
     * @param dValue 默认值
     * @return Object
     */
    @Override
    public Object getOtherProperties(String key, Object dValue) {
        return settingPreferences.getData(key, dValue);
    }

    /**
     * 移除指定KEY
     * 
     * @param key
     */
    public void removeKey(String key) {
        settingPreferences.removeKEY(key);
    }

    /**
     * @return the ctx
     */
    public Context getCtx() {
        return ctx;
    }

    /**
     * @param ctx the ctx to set
     */
    public void setCtx(Context ctx) {
        this.ctx = ctx;
    }

    /**
     * @return the settingPreferences
     */
    public SettingsPreferences getSettingPreferences() {
        return settingPreferences;
    }

    /**
     * @param settingPreferences the settingPreferences to set
     */
    public void setSettingPreferences(SettingsPreferences settingPreferences) {
        this.settingPreferences = settingPreferences;
    }

}
