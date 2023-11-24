package pricePack;
import java.util.ArrayList;
import net.sf.json.JSONArray;
import net.sf.json.JSONObject;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import entity.Price;

/**
 * Servlet implementation class ajaxServlet
 */
@WebServlet("/ajaxPrice")
public class ajaxPrice extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ajaxPrice() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.setCharacterEncoding("utf-8");
		response.getWriter().append("Served at: ").append(request.getContextPath());
		PriceDao pricedao = new PriceDao();
		String aid="20164413";
		ArrayList<Price> Price;
		Price=pricedao.selectPrice(aid);
		if(Price!=null)
		{
			PrintWriter out = response.getWriter();
			out.print("2");
		}
		JSONArray arr= new JSONArray();
		for(Price d:Price){
            JSONObject obj=new JSONObject();
            obj.put("name", d.getName());
            obj.put("age", d.getPid());
            obj.put("end_date", d.getEnd_date());
            obj.put("begin_date", d.getBegin_date());
            obj.put("mode", d.getMode());
            obj.put("aid", d.getAid());

            arr.add(obj);
        }
		if(arr!=null)
		{
			PrintWriter out = response.getWriter();
			out.print("1");
		}
		response.getWriter().append(arr.toString());

	}
	
	
	
	

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
