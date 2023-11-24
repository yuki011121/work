package haoyuNeed;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Vector;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import entity.Reward;

import net.sf.json.JSONArray;
import net.sf.json.JSONObject;

import entity.Price;
import reward_belong_toPack.Reward_belong_to;
import reward_belong_toPack.Reward_belong_toDAO;

/**
 * Servlet implementation class Show2
 */
@WebServlet("/Show2")
public class Show2 extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Show2() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		
		TempDao tempDao = new TempDao();
		Vector<Reward_belong_to> ansRBT = new Vector();
		Vector<Reward> ansRewards = new Vector();
		Reward tempReward = new Reward();
		
 		HttpSession session = request.getSession();
		String aid = (String)session.getAttribute("id");
 		//String aid = "1";
		int i;
		
		request.setCharacterEncoding("UTF-8");
		response.setContentType("text/html; charset=UTF-8");
		System.out.println("进入show2!!!");
		ArrayList<Price> prices = tempDao.selectPrice(aid);
		
		
		JSONArray objArray = new JSONArray();
		JSONObject obj=new JSONObject();
		int nowPid, nowRid;
		int ansTotalPrice = 0;
		int maxLevelRid = -1, maxLevel = -1, nowLevel;


		for(Price nowPrice:prices)
		{
			nowPid = nowPrice.getPid();
			obj.put("pid", Integer.toString(nowPid));
			
			ansRBT = tempDao.selectRBTAccordingToPid(nowPid);
			
			obj.put("priceName", nowPrice.getName());
			obj.put("startTime", nowPrice.getBegin_date().toString());
			obj.put("endTime", nowPrice.getEnd_date().toString());
			obj.put("mode",  Integer.toString(nowPrice.getMode()));
			
			obj.put("rewardLevels",  Integer.toString(ansRBT.size()));
			
			ansTotalPrice = 0;
			maxLevel = -1;
			maxLevelRid = -1;
			Reward_belong_to nowRBT;
			
			for(i = 0; i < ansRBT.size(); i++)
			{
				nowRBT = ansRBT.get(i);
				nowRid = nowRBT.getRid();
				nowLevel = nowRBT.getLlevel();
//				System.out.println("\n" + i+":");
//				System.out.println(nowRid);
//				System.out.println(nowLevel);
				//obj.put(nowRid , nowRid);
				//obj.put(nowLevel, nowLevel);
				if(nowLevel > maxLevel)
				{
					maxLevelRid = nowRid;
					maxLevel = nowLevel;
				}
				
				ansTotalPrice += tempDao.selectRewardPriceAccoringToRid(nowRid);
				
			}
			
			tempReward = tempDao.selectRewardAccoringToRid(maxLevelRid);
			obj.put("topValueRewardName", tempReward.getName());
			obj.put("topValue", Float.toString(tempReward.getPrice()));
			obj.put("totalValue", Integer.toString(ansTotalPrice));
			
			objArray.add(obj);
			
		}
		
		
		
		/*
		String jjson= objArray.toString();
		jjson=jjson.substring(1,jjson.length()-1);
		System.out.println(jjson);
		
		*/
		//PrintWriter out;
		//out.println(objArray.toString());
		//request.setAttribute("thing", objArray.toString());
		//response.getWriter().append(objArray.toString());
		//session.setAttribute("priceInformation", prices);
		//response.sendRedirect("test.jsp");
		
		
		//PrintWriter out=null;
		/*
		out = response.getWriter();
		out.write(objArray.toString());
		out.flush();
		out.close();
		*/
		System.out.println(objArray.toString());
		response.getWriter().print(objArray.toString());
		return;
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
		
	}

}
