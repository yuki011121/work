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


@WebServlet("/ShowActivity")
public class ShowActivity extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public ShowActivity() {
		super();
	}

	/**
	 * Destruction of the servlet. <br>
	 */
	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
		out.println("<HTML>");
		out.println("  <HEAD><TITLE>A Servlet</TITLE></HEAD>");
		out.println("  <BODY>");
		out.print("    This is ");
		out.print(this.getClass());
		out.println(", using the GET method");
		out.println("  </BODY>");
		out.println("</HTML>");
		out.flush();
		out.close();
	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		
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

		//response.getWriter().write(objArray.toString());
		//session.setAttribute("priceInformation", prices);
		
		request.getRequestDispatcher("/TEST_session.jsp").forward(request, response);
	}

	/**
	 * Initialization of the servlet. <br>
	 *
	 * @throws ServletException if an error occurs
	 */
	public void init() throws ServletException {
		// Put your code here
	}

}
