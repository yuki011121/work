package reward_belong_toPack;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Vector;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import net.sf.json.JSONObject;

public class SelectRewards_RBT extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public SelectRewards_RBT() {
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
		doPost(request, response);
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
		
		Reward_belong_toDAO rbtDAO = new Reward_belong_toDAO();
		Vector<Reward_belong_to> ansRBT = new Vector();
		int maxLevelRid = 0, maxLevel = -1, i, tempRid, tempLevel;
		
		request.setCharacterEncoding("UTF-8");
		response.setContentType("text/html; charset=UTF-8");
//		PrintWriter out = response.getWriter();

		ansRBT = rbtDAO.select(Integer.parseInt(request.getParameter("pid")));
		JSONObject obj=new JSONObject();
		obj.put("RewardLevels", ansRBT.size());
		
		for(i = 0; i < ansRBT.size(); i++)
		{
			tempRid = ansRBT.get(i).getRid();
			tempLevel = ansRBT.get(i).getLlevel();
			if(tempLevel > maxLevel)
			{
				maxLevelRid = tempRid;
				maxLevel = tempLevel;
			}
				
		}
		
		obj.put("maxLevelRid", maxLevelRid);
		response.getWriter().write(obj.toString());

		
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
