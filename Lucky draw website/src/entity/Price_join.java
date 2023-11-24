package entity;

import java.sql.Date;

public class Price_join {
	
	private int uid;
	private int pid;
	private String join_channel;
	private String join_loaction;
	private Date join_time;
	public int getUid() {
		return uid;
	}
	public void setUid(int uid) {
		this.uid = uid;
	}
	public int getPid() {
		return pid;
	}
	public void setPid(int pid) {
		this.pid = pid;
	}
	public String getJoin_channel() {
		return join_channel;
	}
	public void setJoin_channel(String join_channel) {
		this.join_channel = join_channel;
	}
	public String getJoin_loaction() {
		return join_loaction;
	}
	public void setJoin_loaction(String join_loaction) {
		this.join_loaction = join_loaction;
	}
	public Date getJoin_time() {
		return join_time;
	}
	public void setJoin_time(Date join_time) {
		this.join_time = join_time;
	}

}
