package rewardPack;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import dataBase.ConnectionManager;
import entity.Reward;

import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

public class RewardDao {
	
	
	
		//插入多个商品
		public int[] add_the_reward(List<Reward> lists)
		{
			Connection conn =ConnectionManager.getConnection();
			String sql = "insert into reward(name,aid,price,file)values(?,?,?,?)";			
			PreparedStatement psm=null;
			try {
				psm =  conn.prepareStatement(sql);
				Iterator<Reward> it = lists.iterator();
				while (it.hasNext()) {
					//Iterator类的next( )方法在同一循环中不能出现两次。
					Reward item= it.next();
					psm.setString(1, item.getName());
					psm.setInt(2, item.getAid());
					psm.setFloat(3, item.getPrice());
					psm.setString(4,item.getFile() );
					psm.addBatch();
			}
				int[] rows= psm.executeBatch();
				return rows;
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			return null;
		}
		
	
	//返回特定的奖品
	public Reward select_the_reward_S(String rname)
	{
		Connection conn =ConnectionManager.getConnection();
		String sql="select * from Reward where name= '"+rname+"'";
		PreparedStatement psm=null;
		ResultSet rs=null;
		Reward reward=null;
		try {
			psm=conn.prepareStatement(sql);
			rs=psm.executeQuery();
			if(rs.next()) {
				reward=new Reward();
				reward.setName(rs.getString("name"));
				reward.setAid(rs.getInt("aid"));
				reward.setPrice(rs.getFloat("price"));
				reward.setRid(rs.getInt("rid"));
			}
			
		}catch(Exception e) {
			e.printStackTrace();
		}
		return reward;
	}
	
	public Reward select_the_reward_ID(int  rid)
	{
		Connection conn =ConnectionManager.getConnection();
		String sql="select * from Reward where rid= '"+rid+"'";
		PreparedStatement psm=null;
		ResultSet rs=null;
		Reward reward=null;
		try {
			psm=conn.prepareStatement(sql);
			rs=psm.executeQuery();
			if(rs.next()) {
				reward=new Reward();
				reward.setName(rs.getString("name"));
				reward.setAid(rs.getInt("aid"));
				reward.setPrice(rs.getFloat("price"));
				reward.setRid(rs.getInt("rid"));
				reward.setFile(rs.getString("file"));
			}
			
		}catch(Exception e) {
			e.printStackTrace();
		}
		return reward;
	}
	
	//根据aid返回所有的奖品
	public List<Reward> select_all_rewards(String a_id)
	{
		//int aid=Integer.parseInt(a_id);
		List<Reward> lists = new ArrayList<Reward>();
		Connection conn =ConnectionManager.getConnection();
		String sql="select * from Reward where aid='"+a_id+"';";
		PreparedStatement psm=null;
		ResultSet rs=null;
		Reward reward=null;
		try {
			psm=conn.prepareStatement(sql);
			rs=psm.executeQuery();
			while(rs.next()) {
				reward=new Reward();
				reward.setName(rs.getString("name"));
				reward.setAid(rs.getInt("aid"));
				reward.setPrice(rs.getFloat("price"));
				reward.setRid(rs.getInt("rid"));
				lists.add(reward);
				System.out.println(reward.getName());
			}
		}catch(Exception e) {
			e.printStackTrace();
		}
		
		return lists;
	}
	
	//删除特定的奖品
	public void delete_the_reward(String rname)
	{
		Connection conn =ConnectionManager.getConnection();
		String sql="delete from Reward where rid='"+rname+"';";
		PreparedStatement psm=null;
		try {
			psm=conn.prepareStatement(sql);
			psm.execute();
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	
	public int modify_name_reward(String old_id,String new_name)
	{
		
		Connection conn =ConnectionManager.getConnection();
		String sql="update reward set name='"+new_name+"' where rid='"+old_id+"';";
		PreparedStatement psm=null;
		try {
			psm=conn.prepareStatement(sql);
			psm.execute();
			return 1;
		}catch(Exception e) {
			e.printStackTrace();
			return 0;
		}
	}
	
	

}
