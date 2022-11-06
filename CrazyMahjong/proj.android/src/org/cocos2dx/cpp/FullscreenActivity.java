package org.cocos2dx.cpp;





import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;

import com.qhbmj.one.mz.R;





public class FullscreenActivity extends Activity {

	
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_fullscreen);

};
protected void onStart() {
	super.onStart();

	new Handler().postDelayed(new Runnable() {
		public void run() {
		    Intent intent = new Intent();  
		    intent.setClass(FullscreenActivity.this, AppActivity.class);  
		    intent.setFlags(intent.FLAG_ACTIVITY_NO_ANIMATION);
		    startActivity(intent);  
	 		
	 		overridePendingTransition(android.R.anim.fade_in,
					android.R.anim.fade_out);
		    
	 		FullscreenActivity.this.finish();

   


		}
	}, 1000);

	

};

}
