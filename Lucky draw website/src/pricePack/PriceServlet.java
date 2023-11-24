package pricePack;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import entity.Price;
import entity.Reward;
import net.sf.json.JSONArray;
import net.sf.json.JSONObject;
import pricePack.PriceDao;

/**
 * Servlet implementation class PriceServlet
 */
@WebServlet("/PriceServlet")
public class PriceServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public PriceServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.setCharacterEncoding("utf-8");
		/*
		HttpSession session  = request.getSession();
		String aid=session.getAttribute("id");
		*/
		
		
		String type = request.getParameter("type");
		System.out.println(type);
		if(type.equals("search_price")) {
	 		//HttpSession session = request.getSession();
			//String aid = (String)session.getAttribute("id");
			String aid="1";
			
			String name=request.getParameter("name");
			System.out.println(name);
			
			PriceDao priceDao = new PriceDao();
			ArrayList<Price> price=new ArrayList<Price>();
			price=priceDao.selectPrice_name(aid,name);
			JSONArray arr= new JSONArray();
			for(Price r:price) {
				JSONObject obj = new JSONObject();
				obj.put("pid",String.valueOf(r.getPid()));
				obj.put("name",r.getName());
				obj.put("End_date",String.valueOf(r.getEnd_date()));
				obj.put("Begin_date",String.valueOf(r.getBegin_date()));
				obj.put("mode",String.valueOf(r.getMode()));
				arr.add(obj);
			}
			System.out.println(arr.toString());
			response.getWriter().append(arr.toString());
			return;
		}
		else if (type.equals("add_price")) {
			String name=request.getParameter("name");
			String begin_date=request.getParameter("begin_date");
			String end_date=request.getParameter("end_date");
			String aid="1";
			String mode=request.getParameter("mode");
			PriceDao priceDao = new PriceDao();
			// PrintWriter out = response.getWriter();
			int count = priceDao.setPrice(name,end_date,begin_date,aid,mode);
			System.out.println(count);
			if(count!=0)
			{
				request.getRequestDispatcher("./new_price_reward_setting.jsp").forward(request, response);
				return;
			}
			else{
				System.out.print("Price创建失败");
				return;
			}
		}
		else if (type.equals("delete_price")) {
			
			System.out.println("进入delete_price");
			String name=request.getParameter("name");
			System.out.println("删除"+name);
			PriceDao priceDao = new PriceDao();
			String aid="1";
			ArrayList<Price> PriceList=new ArrayList<Price>();
			PriceList= priceDao.selectPrice_name(aid,name);
			if(PriceList.size()==0) {
				System.out.println("没有这个奖项");
				response.getWriter().append("{\"ERROR\":\"ture\"}");
			}
			else {
				Price item = PriceList.get(0);
				priceDao.deletePrice(String.valueOf(item.getPid()));
				response.getWriter().append("{\"ERROR\":\"false\"}");
			}
			
			
		}
		
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
