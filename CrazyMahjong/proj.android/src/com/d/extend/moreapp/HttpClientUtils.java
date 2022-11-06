
package com.d.extend.moreapp;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;

import android.util.Log;

import com.tbu.androidtools.util.StringUtils;

/**
 * HTTP工具类
 * 
 * @author bluestome.zhang
 */
public class HttpClientUtils {

    private final static String TAG = HttpClientUtils.class.getCanonicalName();

    /**
     * 验证网址是否可用
     * 
     * @param url
     * @return
     */
    public static boolean urlValidation(String url) {
        boolean success = false;
        URL sUrl = null;
        HttpURLConnection conn = null;
        try {
            sUrl = new URL(url);
            conn = (HttpURLConnection) sUrl.openConnection();
            conn.setConnectTimeout(5 * 1000);
            conn.setReadTimeout(10 * 1000);
            conn.connect();
            if (conn.getResponseCode() == HttpURLConnection.HTTP_OK) {
                success = true;
            }
        } catch (Exception e) {
        } finally {
            if (null != conn) {
                conn.disconnect();
                conn = null;
            }
            if (null != sUrl) {
                sUrl = null;
            }
        }
        return success;
    }

    /**
     * 获取指定URL的内容
     * 
     * @param url
     * @param header 请求头名
     * @param headerValue 请求头值
     * @return
     */
    public static int getBodyLength(String url, String header,
            String headerValue) {
        int value = -1;
        URL cURL = null;
        URLConnection connection = null;
        try {
            cURL = new URL(url);
            connection = cURL.openConnection();
            // 获取输出流
            connection.setDoOutput(true);
            connection.addRequestProperty(header, headerValue);
            connection.setConnectTimeout(5 * 1000);
            connection.setReadTimeout(10 * 1000);
            connection.connect();

            value = connection.getContentLength();
        } catch (Exception e) {
            Log.e(TAG, "ERROR:" + e);
        } finally {
            if (null != connection) {
                connection = null;
            }
        }
        return value;
    }

    /**
     * 获取响应体
     * 
     * @param url 目标地址
     * @return
     */
    public static byte[] getResponseBodyAsByte(String url) {
        byte[] result = null;
        URL urlO = null;
        HttpURLConnection http = null;
        InputStream is = null;
        ByteArrayOutputStream out = null;
        try {
            urlO = new URL(url);
            http = (HttpURLConnection) urlO.openConnection();
            http.setConnectTimeout(5 * 1000);
            http.setReadTimeout(10 * 1000);
            http.connect();
            int code = http.getResponseCode();
            if (code == HttpURLConnection.HTTP_OK) {
                String chunked = http.getHeaderField("Transfer-Encoding");
                if (!StringUtils.isBlank(chunked)) {
                    is = http.getInputStream();
                    out = new ByteArrayOutputStream();
                    byte[] buffer = new byte[256];
                    int c;
                    while (-1 != (c = is.read(buffer))) {
                        out.write(buffer, 0, c);
                    }
                    out.flush();
                    result = out.toByteArray();
                } else {
                    int length = http.getContentLength();
                    if (length > 0) {
                        is = http.getInputStream();
                        byte[] buffer = new byte[1024];
                        out = new ByteArrayOutputStream();
                        int c;
                        while (-1 != (c = is.read(buffer))) {
                            out.write(buffer, 0, c);
                        }
                        out.flush();
                        result = out.toByteArray();
                    } else {
                        is = http.getInputStream();
                        byte[] buffer = new byte[1024];
                        out = new ByteArrayOutputStream();
                        int c;
                        while (-1 != (c = is.read(buffer))) {
                            out.write(buffer, 0, c);
                        }
                        out.flush();
                        result = out.toByteArray();
                    }
                }
            }
        } catch (Exception e) {
            Log.e(TAG, "Exception:" + e.getMessage());
        } finally {
            if (null != is) {
                try {
                    is.close();
                } catch (IOException e) {
                    Log.d(TAG, "InputStream.exception:" + e.getMessage());
                    e.printStackTrace();
                }
            }
            if (null != out) {
                try {
                    out.close();
                } catch (IOException e) {
                }
            }
            if (null != http) {
                http.disconnect();
            }

        }
        return result;
    }
}
