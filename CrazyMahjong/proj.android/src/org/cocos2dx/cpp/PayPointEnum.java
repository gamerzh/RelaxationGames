package org.cocos2dx.cpp;

public enum PayPointEnum {

	FIRSTPAYGFIT(1,3000,"首充礼包"),
	VIPGIFT(2,3800,"会员礼包"),
	COINGIFT(3,3000,"金币礼包"),
	
	COIN_18(4,1800,"商城-18元"),
	
	COIN_28(5,2800,"商城-28元"),
	COIN_58(6,5800,"商城-58元"),
	COIN_88(7,8800, "商城-88元");

	
	private int payPoint;
	private int price;
	private String propName;
	private PayPointEnum(int payPoint,int price,String propName){
		this.payPoint = payPoint;
		this.price = price;
		this.propName = propName;
	}
	
	public int getPayPoint() {
		return payPoint;
	}
	
	public int getPrice() {
		return price;
	}
	public String getPropName() {
		return propName;
	}
	
}
