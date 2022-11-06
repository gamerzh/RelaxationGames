
package com.hifreshday.android.setting;

/**
 * 设置功能接口参数
 * 
 * @author bluestome.zhang
 */
public interface Setting {

    // 背景音乐KEY
    public static final String BGVOICE = "setting_background_voice";

    // 游戏音乐KEY
    public static final String GAMEVOICE = "setting_game_voice";

    // 亮度KEY
    public static final String BRIGHTNESS = "setting_brightness";

    // 震动KEY
    public static final String SHOCK = "setting_shock";

    // 动画KEY
    public static final String ANIMATION = "setting_animation";

    /**
     * AIDL的意图过滤名
     */
    public static final String SERVICE_INTENT_FILTER_NAME = "com.hifreshday.android.setting.service.MusicPlayService.AIDLAction";

    /**
     * 背景音乐调节
     * 
     * @param value 背景音乐值
     */
    boolean adjustBGVoice(Integer value);

    /**
     * 获取背景音量
     * 
     * @return Integer
     */
    Integer getBGVoice();

    /**
     * 游戏音效调节
     * 
     * @param value 游戏音效值
     */
    boolean adjustGameMusic(Integer value);

    /**
     * 获取游戏音量
     * 
     * @return Integer
     */
    Integer getGameMusic();

    /**
     * 亮度调节
     * 
     * @param value 亮度值
     */
    boolean adjustBrightness(Integer value);

    /**
     * 获取亮度值
     * 
     * @return Integer
     */
    Integer getBrightness();

    /**
     * 震动开关调节
     * 
     * @param value 是否开启震动
     */
    boolean shockSwitch(Boolean value);

    /**
     * 获取震动开关设置
     * 
     * @return Boolean
     */
    Boolean getShockValue();

    /**
     * 动画开关调节
     * 
     * @param value 是否开启动画
     */
    boolean animationSwitch(Boolean value);

    /**
     * 获取动画开关设置
     * 
     * @return Boolean
     */
    Boolean getAnimationValue();

    /**
     * 设置其他参数
     * 
     * @param name 键名
     * @param value 值
     */
    boolean setOtherProperties(String name, Object value);

    /**
     * 根据参数名获取参数
     * 
     * @param key 键名
     * @param dValue 默认值
     * @return Object
     */
    Object getOtherProperties(String name, Object dValue);

    /**
     * 移除指定KEY
     * 
     * @param key
     */
    void removeKey(String key);
}
