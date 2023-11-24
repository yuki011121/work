package applecom.entity;

public class Order {
		//定义变量
		//与数据库中orders中定义的名称一致
		
		//订单id
		private int O_id;
		//下单用户邮箱 (apple id)
		private String email;
		//手机名
		private String phonename;
		//屏幕尺寸
		private String screensize;
		//用户生日
		private String color;
		
		
		//获取变量的get和set方法以及toString方法
		public int getO_ID() {
			return O_id;
		}
		public void setO_ID(int O_id) {
			this.O_id=O_id;
		}
		public String getemail() {
			return email;
		}
		public void setemail(String email) {
			this.email=email;
		}
		
		public String getphonename() {
			return phonename;
		}
		public void setphonename(String phonename) {
			this.phonename=phonename;
		}
		
		public String getscreensize() {
			return screensize;
		}
		public void setscreensize(String screensize) {
			this.screensize=screensize;
		}
		
		public String getcolor() {
			return color;
		}
		public void setcolor(String color) {
			this.color=color;
		}
		@Override
		public String toString() {
			return "User [order_id=" + O_id + ", email=" + email + ", phonename=" + phonename + ", "
					+ "screensize=" + screensize + ", color=" + color + "]";
		}
		
}
