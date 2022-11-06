
package com.d.extend.moreapp;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.lang.ref.SoftReference;
import java.net.URLEncoder;
import java.util.HashMap;

import android.os.Environment;
import android.util.Log;

/**
 * 图片工具类
 * 
 * @author bluestome.zhang
 */
public class ImageUtils {

    private final static String TAG = ImageUtils.class.getCanonicalName();
    
    public static final String POXIAO_ROOT_DIR = Environment.getExternalStorageDirectory()
            .getAbsolutePath() + "/.poxiaogame/";
    public static final String IMAGE_PATH = POXIAO_ROOT_DIR + "image/";
    
    private static HashMap<String, SoftReference<byte[]>> byteArrayCache = new HashMap<String, SoftReference<byte[]>>();

    private static GameImpl gameImpl;

    public static void initGameImpl(GameImpl gameImpl) {
        ImageUtils.gameImpl = gameImpl;
    }

    /**
     * 从本地读取图片
     * 
     * @param imgName 图片名称
     * @return byte[] 图片流
     */
    public static byte[] loadImageFromLocal(String imgName) {
        byte[] body = null;
        String fPath = IMAGE_PATH + imgName;
        File file = null;
        try {
            SoftReference<byte[]> cache = byteArrayCache.get(fPath);
            if (null != cache) {
                body = cache.get();
                if (null != body) {
                    return body;
                }
            }
            file = new File(fPath);
            // 对文件名中有二级目录进行本地路径判断处理
            if (!file.getParentFile().exists()) {
                file.getParentFile().mkdirs();
            }
            if (file.exists()) {
                // 读取图片并转成Bitmap
                FileInputStream fis = new FileInputStream(file);
                ByteArrayOutputStream baos = new ByteArrayOutputStream();
                byte[] buffer = new byte[2048];
                int c;
                while ((c = fis.read(buffer)) != -1) {
                    baos.write(buffer, 0, c);
                    baos.flush();
                }
                body = baos.toByteArray();
                baos.close();
                fis.close();
            } else {
                Log.d(TAG, "文件不存在本地[" + fPath + "]");
            }
        } catch (Exception e) {
            Log.e(TAG, "loadImageFromLocal.exception:" + e.getMessage());
        }
        return body;
    }

    /**
     * 从服务端下载图片
     * 
     * @param addr 图片保存的服务器地址
     * @param imgName 图片名称
     * @return
     */
    public static byte[] loadImageFromServer(String addr, String imgName) {
        final String url = addr + imgName;
        byte[] body = null;
        try {
            body = HttpClientUtils.getResponseBodyAsByte(url);
            if (null != body) {
                // 将图片保存到本地
                String fPath = IMAGE_PATH + imgName;
                saveImage2Local(fPath, body);
            }
        } catch (Exception e) {
            Log.e(TAG, "loadImageFromServer.exception:" + e.getMessage());
        }
        return body;
    }

    /**
     * 从服务端下载图片
     * 
     * @param addr 图片保存的服务器地址
     * @param imgName 图片名称
     * @return
     */
    public static byte[] loadImageFromServer(String url) {
        byte[] body = null;
        try {
            body = HttpClientUtils.getResponseBodyAsByte(url);
            if (null != body) {
                Log.d(TAG, "从服务端下载的文件大小为:" + body.length);
                // 将图片保存到本地
                String fPath = IMAGE_PATH + File.separator
                        + URLEncoder.encode(url);
                saveImage2Local(fPath, body);
            }
        } catch (Exception e) {
            Log.e(TAG, "loadImageFromServer.exception:" + e.getMessage());
        }
        return body;
    }

    /**
     * 将图片流保存到本地文件中
     * 
     * @param fPath 图片在本地的地址
     * @param body 图片流
     * @return
     */
    public static boolean saveImage2Local(String fPath, byte[] body) {
        File file = null;
        boolean ok = false;
        try {
            Log.d(TAG, "文件保存路径:" + fPath);
            if (!byteArrayCache.containsKey(fPath)) {
                byteArrayCache.put(fPath, new SoftReference<byte[]>(body));
            }
            file = new File(fPath);
            FileOutputStream fos = new FileOutputStream(file);
            fos.write(body);
            fos.flush();
            fos.close();
            ok = true;
        } catch (Exception e) {
            Log.e(TAG, "saveImage2Local.exception:" + e.getMessage());
        }
        return ok;
    }

    /**
     * 根据道具ID适配图片
     * 
     * @param propId
     * @return
     */
    public static int propImageAdapter(int propId) {
    	return 0;
    }

    void release() {
        byteArrayCache.clear();
    }

    public interface GameImpl {
        int propImageAdapter(int propId);
    }
}
