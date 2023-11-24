package pricePack;
import java.util.ArrayList;

import java.sql.Connection;
import java.sql.Date;
//import java.util.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import dataBase.ConnectionManager;

import entity.Price;

public class PriceDao {
	public ArrayList<Price> selectPrice(String aid)
	{
		Connection conn =ConnectionManager.getConnection();
		String sql="select * from Price where aid="+aid+";";
		
		//"select * from admain where admin_name = '" + user + "' and Pwd = '" + password + "'"
		PreparedStatement psm=null;
		ResultSet rs=null;
		Price price=null;
		ArrayList<Price> Price=new ArrayList<Price>();
		try {
			psm=conn.prepareStatement(sql);
			rs=psm.executeQuery();
			while(rs.next()) {
				price=new Price();
				price.setName(rs.getString("name"));
				price.setPid(rs.getInt("pid"));
				price.setAid(rs.getInt("aid"));
				price.setMode(rs.getInt("mode"));
				price.setEnd_date(rs.getTimestamp("End_date"));
				
				price.setBegin_date(rs.getTimestamp("begin_date"));
				Price.add(price);
			}
			
		}catch(Exception e) {
			e.printStackTrace();
		}
		return Price;
	}
	
		public ArrayList<Price> selectPrice_name(String aid,String name)
		{
			Connection conn =ConnectionManager.getConnection();
			String sql="select * from Price where name= '"+name+ "' and aid="+aid+";";
			System.out.println(sql);
			//"select * from admain where admin_name = '" + user + "' and Pwd = '" + password + "'"
			PreparedStatement psm=null;
			ResultSet rs=null;
			Price price=null;
			ArrayList<Price> Price=new ArrayList<Price>();
			try {
				psm=conn.prepareStatement(sql);
				rs=psm.executeQuery();
				while(rs.next()) {
					price=new Price();
					price.setName(rs.getString("name"));
					price.setPid(rs.getInt("pid"));
					price.setAid(rs.getInt("aid"));
					price.setMode(rs.getInt("mode"));
					price.setEnd_date(rs.getTimestamp("End_date"));
					price.setBegin_date(rs.getTimestamp("begin_date"));
					Price.add(price);
				}
				
			}catch(Exception e) {
				e.printStackTrace();
			}
			return Price;
		}
		
		
	public int setPrice(String name,String end_date,String begin_date,String aid,String mode)
	{
		Connection conn =ConnectionManager.getConnection();
		String sql="insert into Price (name,end_date,begin_date,aid,mode) values ('"+name+"','"+end_date+"','"+begin_date+"','"+aid+"',"+mode+");";
		PreparedStatement psm=null;
		int count = 0;
		try{
			psm=conn.prepareStatement(sql);
			count=psm.executeUpdate();
		}catch(Exception e) {
			e.printStackTrace();
		}
		return count;
	}
	public int deletePrice(String pid)
	{
		Connection conn =ConnectionManager.getConnection();
		String sql="delete from Price where pid="+pid+";";
		PreparedStatement psm=null;
		int count = 0;
		try{
			psm=conn.prepareStatement(sql);
			count=psm.executeUpdate();
			System.out.println("删除成功");
		}catch(Exception e) {
			e.printStackTrace();
		}
		return count;
	}
}
