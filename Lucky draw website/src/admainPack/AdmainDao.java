package admainPack;
import java.sql.*;

//import javax.enterprise.inject.Default;

import dataBase.ConnectionManager;
import entity.Admain;

public class AdmainDao {
	
	public Admain Login(String id,int llevel)
	{
		Connection conn =ConnectionManager.getConnection();
		String sql=new String();
		
		if(llevel==1)
			sql="select * from Admain where id= '"+id+"'";//管理员
		else 
			sql="select * from user where id= '"+id+"'";//用户
		
		
		//"select * from admain where admin_name = '" + user + "' and Pwd = '" + password + "'"
		PreparedStatement psm=null;
		ResultSet rs=null;
		Admain admain=null;
		try {
			psm=conn.prepareStatement(sql);
			rs=psm.executeQuery();
			if(rs.next()) {
				admain=new Admain();
				admain.setName(rs.getString("name"));
				admain.setPass(rs.getString("pass"));
				admain.setId(rs.getString("id"));
				admain.setLevel(rs.getInt("llevel"));
				admain.setReg_date(rs.getDate("reg_date"));
				admain.setGeo_point(rs.getString("geo_point"));
				admain.setEmail(rs.getString("email"));
				admain.setStatus(rs.getInt("status"));
				
			}
			
		}catch(Exception e) {
			e.printStackTrace();
		}
		return admain;
	}
	

	
	
	public Admain LoginByEmail(String email,int llevel){
		Connection conn =ConnectionManager.getConnection();
		String sql=new String();
		PreparedStatement psm=null;
		ResultSet rs=null;
		if(llevel==1)
			sql="select * from Admain where email= '"+email+"'";//管理员
		else 
			sql="select * from user where email= '"+email+"'";//用户
		
		
		//"select * from admain where admin_name = '" + user + "' and Pwd = '" + password + "'"
		
		Admain admain=null;
		try {
			psm=conn.prepareStatement(sql);
			rs=psm.executeQuery();
			if(rs.next()) {
				admain=new Admain();
				admain.setName(rs.getString("name"));
				admain.setPass(rs.getString("pass"));
				admain.setId(rs.getString("id"));
				admain.setLevel(rs.getInt("llevel"));
				admain.setReg_date(rs.getDate("reg_date"));
				admain.setGeo_point(rs.getString("geo_point"));
				admain.setEmail(rs.getString("email"));
				admain.setStatus(rs.getInt("status"));
			}
			
		}catch(Exception e) {
			e.printStackTrace();
		}
		return admain;
	}
	
	//向数据库写入
	public void Register(String name,String pass,String email,int llevel) throws SQLException{	
		PreparedStatement stmt;
		String sql;
		if(llevel==1)
	    	   sql = "insert into admain(name,pass,llevel,reg_date,geo_point,email,status)  values (?,?,?,?,?,?,?)";
	       else 
	    	   sql = "insert into user(name,pass,llevel,reg_date,geo_point,email,status)  values (?,?,?,?,?,?,?)";
		Connection conn =ConnectionManager.getConnection();
		 
		try {
			
			stmt = (PreparedStatement) conn.prepareStatement(sql);
			
			stmt.setString(1, name);
			stmt.setString(2, pass);
			stmt.setInt(3, llevel);
			stmt.setDate(4, null);
			stmt.setString(5, null);
			stmt.setString(6,email);
			stmt.setInt(7, 0);
			stmt.executeUpdate();
			
		} catch (SQLException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		}
		
	}
	
	public static void setStatusByEmail(String email,int llevel){
		
		PreparedStatement stmt;
		String sql;
		if(llevel==1)
			sql=" update admain set status =1 where email='"+email+"'";//管理员
		else 
			sql=" update user set status =1 where email='"+email+"'";//用户
		Connection conn =ConnectionManager.getConnection();
		try {
			
			stmt = (PreparedStatement) conn.prepareStatement(sql);
			stmt.executeUpdate();
			
		} catch (SQLException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		}
		//System.out.print("status=1");
		  
	}
	
	/*public static int getID(String email,int llevel) throws SQLException{
		String sql;
		Connection conn =ConnectionManager.getConnection();
		if(llevel==1)
			sql="select id from Admain where email= '"+email+"'";//管理员
		else 
			sql="select id from user where email= '"+email+"'";//用户
		PreparedStatement psm=conn.prepareStatement(sql);
		ResultSet rs=psm.executeQuery();
		return(rs.getInt("id"));
	}*/
	
	
}
