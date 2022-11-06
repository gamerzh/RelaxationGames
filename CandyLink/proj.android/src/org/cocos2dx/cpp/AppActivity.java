/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2017 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;

public class AppActivity extends Cocos2dxActivity {

	private static AppActivity appActivity;
	public static native void dreamCallBack(int code,int result);

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		appActivity = this;
	}

	public static void quit() {
		// 弹出对话框
		new Thread(new Runnable() {
			@Override
			public void run() {
				Handler handler = new Handler(Looper.getMainLooper());
				handler.post(new Runnable() {
					@Override
					public void run() {
						AlertDialog dialog = new AlertDialog.Builder(appActivity).setTitle("提示")
								.setPositiveButton("确定", new OnClickListener() {

									@Override
									public void onClick(DialogInterface dialog, int which) {
										// 处理确认按钮的点击事件
										appActivity.finish();
									}
								}).setNegativeButton("取消", null).setMessage("退出游戏").create();
						dialog.show();
					}
				});
			}
		}).start();
	}

	public static void dreamConfirm(int id) {
		String content = "";
		if (id == 1) {
			content = "是否花费10元购买10个提示道具";
		} else if (id == 2) {
			content = "是否花费20元购买5个复活道具";
		} else if (id == 3) {
			content = "是否花费10元购买10个提示道具";
		} else if (id == 4) {
			content = "是否花费10元购买10个重排道具";
		}else if (id == 5) {
			content = "是否花费10元购买10个加时道具";
		}
		getProp(id,content);
	}

	private static void getProp(final int id,final String content) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				Handler handler = new Handler(Looper.getMainLooper());
				handler.post(new Runnable() {
					@Override
					public void run() {
						AlertDialog dialog = new AlertDialog.Builder(appActivity).setTitle("购买")
								.setPositiveButton("确定", new OnClickListener() {

									@Override
									public void onClick(DialogInterface dialog, int which) {
										// 处理确认按钮的点击事件
										dreamCallBack(id,1);
									}
								}).setNegativeButton("取消", new OnClickListener() {

									@Override
									public void onClick(DialogInterface dialog, int which) {
										// 处理确认按钮的点击事件
										dreamCallBack(id,0);
									}
								}).setMessage(content).create();
						dialog.show();
					}
				});
			}
		}).start();
	}
}
