package com.cand.single.nopay;

import com.andy.canvasgame.service.GameConstantsService;

import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;

public class ScaleViewAndAllChildsHelper {

	public static void scaleUp(View view){
		if(view == null || view.getVisibility() == View.INVISIBLE || view.getVisibility() == View.GONE){
			return;
		}
		doScaleUpView(view);
		if(view instanceof ViewGroup){
			ViewGroup viewGroup = (ViewGroup)view;
			int childCount  = viewGroup.getChildCount();
			for(int i=0;i<childCount;i++){
				scaleUp(viewGroup.getChildAt(i));
			}
		}
	}
	
	private static void doScaleUpView(View view){
		
		ScaleViewHelper.scaleUpView(view);
	}
	
}
