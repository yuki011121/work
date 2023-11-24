package rewardPack;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import rewardPack.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;
import entity.Reward;
import net.sf.json.JSONArray;
import net.sf.json.JSONObject;;
/**
 * Servlet implementation class RewardServlet
 */
@WebServlet("/RewardServlet")
public class RewardServlet extends HttpServlet {
	HttpSession session;
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public RewardServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		System.out.println("进入get方法!");
		session =request.getSession();
		response.setCharacterEncoding("utf-8");
		String type=request.getParameter("type");
		if(type.equals("add_reward")) {
			String name=request.getParameter("name");
			String price =request.getParameter("price");
			//String aid = (String)session.getAttribute("id");
			String aid="1";
			Reward one_reward =new Reward();
			one_reward.setAid(Integer.parseInt(aid));
			one_reward.setName(name);
			one_reward.setPrice(Float.parseFloat(price));
			one_reward.setFile(name+".jpg");
			RewardDao tool =  new RewardDao();
			List<Reward> rlists = new ArrayList<Reward>();
			rlists.add(one_reward);
			tool.add_the_reward(rlists);
			System.out.println("结束get方法!");
			request.getRequestDispatcher("/AddReward.jsp").forward(request, response); 
			return;
		}
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		System.out.println("进入Reward的post方法!");
		doGet(request, response);
		session =request.getSession();
		response.setCharacterEncoding("utf-8");
		String type=request.getParameter("type");
		System.out.println(type);
		if(type.equals("new_price_setting_list")) {
			System.out.println("进入new_price_setting_list");
			String aid=request.getParameter("aid");
			RewardDao tool =  new RewardDao();
			List<Reward> lists = new ArrayList<Reward>();
			lists=tool.select_all_rewards(aid);
			JSONArray arr= new JSONArray();
			for(Reward r:lists) {
				JSONObject obj = new JSONObject();
				obj.put("rid",String.valueOf(r.getRid()));
				obj.put("name",r.getName());
				obj.put("price",String.valueOf(r.getPrice()));
				obj.put("imgurl", r.getFile());
				arr.add(obj);
			}
			System.out.println(arr.toString());
			response.getWriter().append(arr.toString());
			return;
		}
		else if(type.equals("modify_reward_name")) {
			System.out.println("进入modify_reward_name");
			String aid=request.getParameter("aid");
			String old_id = request.getParameter("old_id");
			String new_name = request.getParameter("new_name");

			List<Reward> lists = new ArrayList<Reward>();
			RewardDao tool =  new RewardDao();
			int status;
			status=tool.modify_name_reward(old_id,new_name);
			if(status==0) {

				response.getWriter().append("{\"status\": \"error\" }");
			}
			else if(status==1){
				
				response.getWriter().append("{\"status\": \"ok\" }");
			}
			return;
		}
		else if(type.equals("delete_reward")) {
			System.out.println("进入delete_price,old_id");
			String old_id = request.getParameter("id");
			System.out.println(old_id);
			RewardDao tool =  new RewardDao();
			tool.delete_the_reward(old_id);
			response.getWriter().append("{ }");
			return;
			
		}
		
		
		System.out.println("结束post方法!");
	}

}
