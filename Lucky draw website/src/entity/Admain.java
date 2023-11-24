package entity;

public class Admain {
	private String email;
	private String id;
	private String pass;
	private int level; //参与者优先级
	private java.util.Date  reg_date;
	private String   geo_point;
	private int status;
	private String name;
	
	public int getLevel() {
		return level;
	}
	public void setLevel(int level) {
		this.level = level;
	}
	public String getPass() {
		return pass;
	}
	public void setPass(String pass) {
		this.pass = pass;
	}
	public String getGeo_point() {
		return geo_point;
	}
	public void setGeo_point(String geo_point) {
		this.geo_point = geo_point;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public int getStatus() {
		return status;
	}
	public void setStatus(int status) {
		this.status = status;
	}
	public java.util.Date getReg_date() {
		return reg_date;
	}
	public void setReg_date(java.util.Date reg_date) {
		this.reg_date = reg_date;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	
	
}
