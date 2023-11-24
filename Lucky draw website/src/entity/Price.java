package entity;
import java.sql.Timestamp;
public class Price {
	private String name;
	private int pid;
	private Timestamp end_date;
	private int mode; //参与者优先级
	private Timestamp  begin_date;
	private int aid;
	
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getPid() {
		return pid;
	}
	public void setPid(int pid) {
		this.pid = pid;
	}
	public int getMode() {
		return mode;
	}
	public void setMode(int mode) {
		this.mode = mode;
	}
	public Timestamp getEnd_date() {
		return end_date;
	}
	public void setEnd_date(Timestamp end_date) {
		this.end_date = end_date;
	}

	public Timestamp getBegin_date() {
		return begin_date;
	}
	public void setBegin_date(Timestamp begin_date) {
		this.begin_date = begin_date;
	}
	public int getAid() {
		return aid;
	}
	public void setAid(int aid) {
		this.aid = aid;
	}
	
}
