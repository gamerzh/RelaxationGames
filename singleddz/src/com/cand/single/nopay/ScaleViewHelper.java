package com.cand.single.nopay;

import com.andy.canvasgame.service.GameConstantsService;

import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.ViewGroup.MarginLayoutParams;

public class ScaleViewHelper {

	public static void scaleUpView(View view){
		if(view == null ){
			return;
		}
		int width = Math.max(GameConstantsService.getInstance().screenHeight, GameConstantsService.getInstance().screenWidth); 
		if(width==800){
			return;
		}
		scaleUpView(view, width * 1.0f/800);
	}
	
	
	public static void scaleUpView(View view, float scaleUpRate){
		LayoutParams params = view.getLayoutParams();
		int width = (int) (view.getWidth() * scaleUpRate);
		int height =(int) (view.getHeight() * scaleUpRate);
		if(width == 0 && height == 0){
			return;
		}
		params.width = width;
		params.height = height;
		
		
		
		view.setLayoutParams(params);
	}
	
	public static void scaleMargin(View view){
		MarginLayoutParams params = (MarginLayoutParams)view.getLayoutParams();
		int left = (int) (params.leftMargin * GameConstantsService.getInstance().getScaleUpRate());
		int top = (int) (params.topMargin * GameConstantsService.getInstance().getScaleUpRate());
		int right = (int) (params.rightMargin * GameConstantsService.getInstance().getScaleUpRate());
		int bottom = (int) (params.bottomMargin * GameConstantsService.getInstance().getScaleUpRate());
		params.setMargins(left, top, right, bottom);
		view.setLayoutParams(params);
		
	}
	
}
