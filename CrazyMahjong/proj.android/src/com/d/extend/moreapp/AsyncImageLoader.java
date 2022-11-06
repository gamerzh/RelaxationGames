package com.d.extend.moreapp;

import java.lang.ref.SoftReference;
import java.net.URLEncoder;
import java.util.HashMap;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class AsyncImageLoader {

    private String imageServerPrefix = null;
    private HashMap<String, SoftReference<Drawable>> drawableCache;
    private HashMap<String, SoftReference<Bitmap>> bitMapCache;
    private static final String TAG = AsyncImageLoader.class.getCanonicalName();

    public AsyncImageLoader() {
        this.drawableCache = new HashMap<String, SoftReference<Drawable>>();
        this.bitMapCache = new HashMap<String, SoftReference<Bitmap>>();
    }

    public AsyncImageLoader(String imageServerPrefix) {
        this.imageServerPrefix = imageServerPrefix;
        this.drawableCache = new HashMap<String, SoftReference<Drawable>>();
        this.bitMapCache = new HashMap<String, SoftReference<Bitmap>>();
    }

    public Drawable loadDrawable(final String imageName, final ImageCallback imageCallback) {
        final String imageUrl = URLEncoder.encode(imageName);
        Drawable drawable = null;
        if (drawableCache.containsKey(imageUrl)) {
            SoftReference<Drawable> softReference = drawableCache.get(imageUrl);
            drawable = softReference.get();
            if (drawable != null) {
                return drawable;
            }
        }
        // TODO 从本地读取图片
        byte[] body = ImageUtils.loadImageFromLocal(imageUrl);
        if (null != body && body.length > 0) {
            BitmapFactory.Options opt = new BitmapFactory.Options();
            drawable = new BitmapDrawable(BitmapFactory.decodeByteArray(body, 0,
                    body.length, opt));
            drawableCache.put(imageUrl, new SoftReference<Drawable>(drawable));
            return drawable;
        }
        final Handler handler = new Handler() {
            public void handleMessage(Message message) {
                drawableCache.put(imageUrl, new SoftReference<Drawable>((Drawable) message.obj));
                if (null != imageCallback) {
                    imageCallback.imageLoaded((Drawable) message.obj, imageName);
                }
            }
        };
        new Thread() {
            @Override
            public void run() {
                byte[] body = ImageUtils.loadImageFromServer(imageName);
                if (null != body && body.length > 0) {
                    Drawable drawable = null;
                    BitmapFactory.Options opt = new BitmapFactory.Options();
                    drawable = new BitmapDrawable(BitmapFactory.decodeByteArray(body, 0,
                            body.length, opt));
                    Message message = handler.obtainMessage(0, drawable);
                    handler.sendMessage(message);
                } else {
                    Log.d(TAG, ">> 下载图片失败...");
                }
            }
        }.start();
        return null;
    }

    public Drawable loadDrawable(final String imageUrl) {
        Drawable drawable = null;
        if (drawableCache.containsKey(imageUrl)) {
            SoftReference<Drawable> softReference = drawableCache.get(URLEncoder.encode(imageUrl));
            drawable = softReference.get();
            if (drawable != null) {
                Log.d(TAG, "缓存中存在图片，从缓存读取图片:" + imageUrl);
                return drawable;
            }
        }
        // TODO 从本地读取图片
        byte[] body = ImageUtils.loadImageFromLocal(URLEncoder.encode(imageUrl));
        if (null != body && body.length > 0) {
            Log.d(TAG, "缓存中不存在图片，从本地读取图片:" + imageUrl);
            BitmapFactory.Options opt = new BitmapFactory.Options();
            drawable = new BitmapDrawable(BitmapFactory.decodeByteArray(body, 0,
                    body.length, opt));
            drawableCache.put(URLEncoder.encode(imageUrl), new SoftReference<Drawable>(drawable));
            return drawable;
        }
        new Thread() {
            @Override
            public void run() {
                Log.d(TAG, "缓存和本地都不存在图片,从服务端下载图片...," + imageUrl);
                byte[] body = ImageUtils.loadImageFromServer(imageUrl);
                if (null != body && body.length > 0) {
                    Log.d(TAG, "下载成功...,图片大小为:" + body.length);
                    Drawable drawable = null;
                    BitmapFactory.Options opt = new BitmapFactory.Options();
                    drawable = new BitmapDrawable(BitmapFactory.decodeByteArray(body, 0,
                            body.length, opt));
                    drawableCache.put(URLEncoder.encode(imageUrl), new SoftReference<Drawable>(
                            drawable));
                } else {
                    Log.d(TAG, "下载图片失败...");
                }
            }
        }.start();
        return null;
    }

    public Bitmap loadBitmap(final String imageUrl) {
        Bitmap bitMap = null;
        if (bitMapCache.containsKey(imageUrl)) {
            SoftReference<Bitmap> softReference = bitMapCache.get(imageUrl);
            bitMap = softReference.get();
            if (bitMap != null) {
                Log.d(TAG, "缓存中存在图片，从缓存读取图片:" + imageUrl);
                return bitMap;
            }
        }
        // TODO 从本地读取图片
        byte[] body = ImageUtils.loadImageFromLocal(URLEncoder.encode(imageUrl));
        if (null != body && body.length > 0) {
            Log.d(TAG, "缓存中不存在图片，从本地读取图片:" + URLEncoder.encode(imageUrl));
            BitmapFactory.Options opt = new BitmapFactory.Options();
            bitMap = BitmapFactory.decodeByteArray(body, 0,
                    body.length, opt);
            bitMapCache.put(imageUrl, new SoftReference<Bitmap>(bitMap));
            return bitMap;
        }

        // TODO 异步从服务端下载图片
        new Thread() {
            @Override
            public void run() {
                Log.d(TAG, "缓存和本地都不存在图片,从服务端下载图片...," + imageUrl);
                byte[] body = ImageUtils.loadImageFromServer(imageUrl);
                if (null != body && body.length > 0) {
                    Log.d(TAG, "下载成功...,图片大小为:" + body.length);
                    Bitmap bitMap = null;
                    BitmapFactory.Options opt = new
                            BitmapFactory.Options();
                    bitMap = BitmapFactory.decodeByteArray(body, 0,
                            body.length, opt);
                    bitMapCache.put(imageUrl, new SoftReference<Bitmap>(bitMap));
                } else {
                    Log.d(TAG, "下载图片失败...");
                }
            }
        }.start();
        return null;
    }

    public Bitmap loadBitmap(final String imageName, final ImageCallback imageCallback) {
        final String imageUrl = imageServerPrefix + imageName;
        Bitmap bitMap = null;
        if (bitMapCache.containsKey(imageUrl)) {
            SoftReference<Bitmap> softReference = bitMapCache.get(imageUrl);
            bitMap = softReference.get();
            if (bitMap != null) {
                Log.d(TAG, "缓存中存在图片，从缓存读取图片:" + imageName);
                return bitMap;
            }
        }
        // TODO 从本地读取图片
        byte[] body = ImageUtils.loadImageFromLocal(imageName);
        if (null != body && body.length > 0) {
            Log.d(TAG, "缓存中不存在图片，从本地读取图片:" + imageName);
            BitmapFactory.Options opt = new BitmapFactory.Options();
            bitMap = BitmapFactory.decodeByteArray(body, 0,
                    body.length, opt);
            bitMapCache.put(imageUrl, new SoftReference<Bitmap>(bitMap));
            return bitMap;
        }

        // TODO 异步从服务端下载图片
        new Thread() {
            @Override
            public void run() {
                Log.d(TAG, "缓存和本地都不存在图片,从服务端下载图片...," + imageUrl);
                byte[] body = ImageUtils.loadImageFromServer(imageServerPrefix, imageName);
                if (null != body && body.length > 0) {
                    Log.d(TAG, "下载成功...,图片大小为:" + body.length);
                    Bitmap bitMap = null;
                    BitmapFactory.Options opt = new
                            BitmapFactory.Options();
                    bitMap = BitmapFactory.decodeByteArray(body, 0,
                            body.length, opt);
                    bitMapCache.put(imageUrl, new SoftReference<Bitmap>(bitMap));
                    if (null != imageCallback) {
                        imageCallback.imageLoaded(bitMap, imageUrl);
                    }
                } else {
                    Log.d(TAG, "下载图片失败...");
                }
            }
        }.start();
        return null;
    }

    public interface ImageCallback {
        public void imageLoaded(Drawable imageDrawable, String imageUrl);

        public void imageLoaded(Bitmap bitMap, String imageUrl);
    }
}
