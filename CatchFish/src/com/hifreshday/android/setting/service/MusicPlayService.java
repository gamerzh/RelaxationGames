/**
 * 
 */

package com.hifreshday.android.setting.service;

import java.io.IOException;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.res.Resources.NotFoundException;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.SoundPool;
import android.media.SoundPool.OnLoadCompleteListener;
import android.net.Uri;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import com.hifreshday.android.setting.aidl.MusicPlayAidlService;

/**
 * 音乐播放服务
 * 
 * @author bluestome.zhang
 */
public class MusicPlayService extends Service {

    private static String TAG = MusicPlayService.class.getCanonicalName();
    boolean playFlag = false;
    SoundPool soundPool;
    MediaPlayer mediaPlayer;

    @Override
    public void onCreate() {
        Log.d(TAG, ">>> " + TAG + ".onCreate");
        super.onCreate();
        soundPool = new SoundPool(20, AudioManager.STREAM_MUSIC, 0);
        mediaPlayer = new MediaPlayer();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (null == soundPool) {
            soundPool = new SoundPool(10, AudioManager.STREAM_MUSIC, 0);
        }
        if (null == mediaPlayer) {
            mediaPlayer = new MediaPlayer();
        }
        return START_NOT_STICKY;
    }

    @Override
    public IBinder onBind(Intent arg0) {
        return binder;
    }

    public MusicPlayAidlService.Stub binder = new MusicPlayAidlService.Stub() {

        private int resId;
        private int END = -2;
        private int IDLE = -1;
        private int STATE = IDLE;
        private int PREPARE = 0;
        private int START = 1;
        private int PAUSE = 2;
        private int STOP = 3;
        private int CURRENT_POS = 0;

        @Override
        public synchronized void bgMusicInit(int resId) throws RemoteException {
            STATE = IDLE;
            if (null == mediaPlayer) {
                mediaPlayer = new MediaPlayer();
            }
            this.resId = resId;
            if (playFlag && null != mediaPlayer) {
                // 说明有音乐在播放,则停止当前播放的音乐
                mediaPlayer.stop();
            }
            mediaPlayer.reset();
            // TODO 获取系统音量
            float volumn = (float) getAudioVolumn();
            float maxVolumn = (float) getAudioMaxVolumn();
            Log.d(TAG, "系统音量:" + volumn);
            float v = volumn / maxVolumn * 0.30f;
            Log.d(TAG, "缩小后的音量:" + v);
            mediaPlayer.setVolume(v, v);
            try {
                mediaPlayer.setDataSource(getApplicationContext(),
                        Uri.parse("android.resource://" + getApplicationContext().getPackageName()
                                + "/" + resId));
            } catch (IllegalArgumentException e) {
                Log.e(TAG, "IllegalArgumentException:" + e.getMessage());
            } catch (SecurityException e) {
                Log.e(TAG, "SecurityException:" + e.getMessage());
            } catch (IllegalStateException e) {
                Log.e(TAG, "IllegalStateException:" + e.getMessage());
            } catch (IOException e) {
                Log.e(TAG, "IOException:" + e.getMessage());
            }
            try {
                mediaPlayer.prepare();
                STATE = PREPARE;
            } catch (IllegalStateException e) {
                Log.e(TAG, "IllegalStateException:" + e.getMessage());
            } catch (IOException e) {
                Log.e(TAG, "IOException:" + e.getMessage());
            }
        }

        /**
         * 播放游戏音效
         */
        @Override
        public synchronized void gameMusicPlay(final int resId) throws RemoteException {
            try {
                soundPool.load(MusicPlayService.this, resId, 1);
                soundPool.setOnLoadCompleteListener(new
                        OnLoadCompleteListener() {
                            @Override
                            public void onLoadComplete(SoundPool sp, int id, int status)
                            {
                                if (status == 0) {
                                    if (id != -1 && id < 255) {
                                        try {
                                            sp.play(id, 1.0f, 1.0f, 1, 0, 1f);
                                        } catch (Exception e) {
                                            Log.e(TAG, e.getMessage());
                                            releaseSoundPool();
                                        }
                                    } else {
                                        resetSoundPool(resId);
                                    }
                                } else {
                                    resetSoundPool(resId);
                                }
                            }
                        });
            } catch (NotFoundException e) {
                Log.e(TAG, "Game Music Resource NOT FOUND");
                releaseSoundPool();
            }
        }

        /**
         * 释放SoundPool资源
         */
        private void releaseSoundPool() {
            soundPool.release();
            soundPool = new SoundPool(10, AudioManager.STREAM_MUSIC, 1);
        }

        /**
         * 重置SoundPool
         * 
         * @param resI
         */
        private synchronized void resetSoundPool(final int resID) {
            Log.e(TAG, "release SoundPool");
            soundPool.release();
            soundPool = new SoundPool(10, AudioManager.STREAM_MUSIC, 1);
            try {
                soundPool.load(MusicPlayService.this, resID, 1);
                soundPool.setOnLoadCompleteListener(new
                        OnLoadCompleteListener() {
                            @Override
                            public void onLoadComplete(SoundPool sp, int id, int status)
                            {
                                if (status == 0) {
                                    if (id != -1 && id < 255) {
                                        try {
                                            sp.play(id, 1.0f, 1.0f, 1, 0, 1f);
                                        } catch (Exception e) {
                                            Log.e(TAG, e.getMessage());
                                            releaseSoundPool();
                                        }
                                    } else {
                                        resetSoundPool(resID);
                                    }
                                } else {
                                    resetSoundPool(resID);
                                }
                            }
                        });
            } catch (NotFoundException e) {
                Log.e(TAG, "Game Music Resource NOT FOUND");
                releaseSoundPool();
            }
        }

        /**
         * 播放背景音乐
         */
        @Override
        public synchronized void bgMusicPlay(final boolean loop)
                throws RemoteException {
            try {
                if (STATE != PREPARE) {
                    if (resId == 0) {
                        throw new RuntimeException("BACKGROUND MUSIC RESOURCE IS NULL," + resId);
                    }
                    bgMusicInit(this.resId);
                }
                mediaPlayer.setLooping(loop);
                if (CURRENT_POS > 0) {
                    mediaPlayer.seekTo(CURRENT_POS);
                }
                mediaPlayer.start();
                STATE = START;
                mediaPlayer.setOnCompletionListener(new OnCompletionListener() {

                    @Override
                    public void onCompletion(MediaPlayer mp) {
                        Log.d(TAG, "mediaplay is completed:");
                    }
                });
                mediaPlayer.setOnErrorListener(new OnErrorListener() {
                    @Override
                    public boolean onError(MediaPlayer mp, int what, int extr) {
                        mp.reset();
                        return false;
                    }
                });
                playFlag = true;
            } catch (IllegalArgumentException e) {
                Log.e(TAG, "IllegalArgumentException:" + e.getMessage());
                playFlag = false;
            } catch (SecurityException e) {
                Log.e(TAG, "SecurityException:" + e.getMessage());
                playFlag = false;
            } catch (IllegalStateException e) {
                Log.e(TAG, "IllegalStateException:" + e.getMessage());
                playFlag = false;
            } catch (NotFoundException e) {
                Log.e(TAG, "BACKGROUND Music Resource[" + resId + "] NOT FOUND");
            }
        }

        /**
         * 停止背景音乐播放
         * 
         * @throws RemoteException
         */
        @Override
        public synchronized void bgMusicStop() throws RemoteException {
            // 新增对播放状态的判断
            if (null != mediaPlayer && playFlag && (STATE == START || STATE == PAUSE)) {
                mediaPlayer.stop();
                mediaPlayer.release();
                mediaPlayer = null;
            }
            if (null != soundPool) {
                soundPool.release();
                soundPool = null;
            }
            reset();
        }

        public synchronized void adjustBgMusicVolume(float v) {
            if (null != mediaPlayer) {
                mediaPlayer.setVolume(v, v);
            }
        }

        /**
         * 背景音乐暂停
         */
        @Override
        public synchronized void bgMusicPause() throws RemoteException {
            int pos = mediaPlayer.getCurrentPosition();
            // 新增对播放状态的判断
            if (null != mediaPlayer && mediaPlayer.isPlaying() && (pos > 0) && (STATE == START)) {
                mediaPlayer.pause();
                CURRENT_POS = mediaPlayer.getCurrentPosition();
            }
            STATE = PAUSE;
            playFlag = false;
        }

        /**
         * 背景音乐恢复
         * 
         * @throws RemoteException
         */
        @Override
        public synchronized void bgMusicResume() throws RemoteException {
            try {
                if (STATE == PAUSE && !playFlag) {
                    if (null != mediaPlayer && !playFlag) {
                        if (CURRENT_POS > 0) {
                            mediaPlayer.seekTo(CURRENT_POS);
                        }
                        mediaPlayer.start();
                    }
                    playFlag = true;
                    STATE = START;
                } else {
                    STATE = STOP;
                    // 当处于非发状态时，则重新播放背景音乐
                    bgMusicPlay(true);
                }
            } catch (IllegalStateException e) {
                STATE = STOP;
                // 当处于非发状态时，则重新播放背景音乐
                bgMusicPlay(true);
            }
        }

        @Override
        public void bgMusicPlay2(int resId, boolean loop) throws RemoteException {
            bgMusicInit(resId);
            bgMusicPlay(loop);
        }

        /**
         * 重置相关参数
         */
        private void reset() {
            STATE = STOP;
            playFlag = false;
            CURRENT_POS = 0;
        }

        @Override
        public int getBGState() throws RemoteException {
            return STATE;
        }
    };

    @Override
    public void onDestroy() {
        Log.d(TAG, ">>> " + TAG + ".onDestroy");
        super.onDestroy();
        if (null != mediaPlayer) {
            mediaPlayer.release();
            mediaPlayer = null;
        }
        if (null != soundPool) {
            soundPool.release();
            soundPool = null;
        }
        playFlag = false;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        Log.d(TAG, ">>> " + TAG + ".onUnbind");
        return super.onUnbind(intent);
    }

    /**
     * 获取系统的音量值
     * 
     * @param activity
     * @return
     */
    protected int getAudioVolumn() {
        AudioManager mAudioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
        int mVolume = mAudioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
        return mVolume;
    }

    /**
     * 获取系统中类型为STREAM_MUSIC的最大音量
     * 
     * @param activity
     * @return
     */
    protected int getAudioMaxVolumn() {
        AudioManager mAudioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
        int max = mAudioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
        return max;
    }
}
