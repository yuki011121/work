package applecom.entity;


public class User {
	//定义变量
	//与数据库中user中定义的名称一致
	
	//用户id
	private int id;
	//用户姓氏
	private String surname;
	//用户名字
	private String givenname;
	//用户所在地区
	private String region;
	//用户生日
	private String birthday;
	//邮箱作为Apple ID
	private String email;
	//用户密码
	private String pwd;
	//用户电话
	private String tel;
	
	//获取变量的get和set方法以及toString方法
	public int getID() {
		return id;
	}
	public void setID(int id) {
		this.id=id;
	}
	
	public String getsurname() {
		return surname;
	}
	public void setsurname(String surname) {
		this.surname=surname;
	}
	
	public String getgivenname() {
		return givenname;
	}
	public void setgivenname(String givenname) {
		this.givenname=givenname;
	}
	
	public String getregion() {
		return region;
	}
	public void setregion(String region) {
		this.region=region;
	}
	
	public String getbirthday() {
		return birthday;
	}
	public void setbirthday(String birthday) {
		this.birthday=birthday;
	}
	
	public String getemail() {
		return email;
	}
	public void setemail(String email) {
		this.email=email;
	}
	
	public String getpwd() {
		return pwd;
	}
	public void setpwd(String pwd) {
		this.pwd=pwd;
	}
	
	public String gettel() {
		return tel;
	}
	public void settel(String tel) {
		this.tel=tel;
	}
	
	@Override
	public String toString() {
		return "User [id=" + id + ", surname=" + surname + ", givenname=" + givenname + ", "
				+ "region=" + region + ", birthday=" + birthday + ", email=" + email + ", "
						+ " password=" + pwd + ", tel=" + tel + "]";
	}
}
