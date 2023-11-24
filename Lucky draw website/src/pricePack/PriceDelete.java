package pricePack;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * Servlet implementation class PriceDelete
 */
@WebServlet("/PriceDelete")
public class PriceDelete extends HttpServlet {
	private static final long serialVersionUID = 1L;
	HttpSession session;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public PriceDelete() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.setCharacterEncoding("utf-8");
		
		
		session =request.getSession();
		String aid = (String )session.getAttribute("id");
		
		
		
		response.getWriter().append("Served at: ").append(request.getContextPath());
		String pid=request.getParameter("pid");
		PriceDao priceDao = new PriceDao();
		PrintWriter out = response.getWriter();
		int count = priceDao.deletePrice(pid);
		if(count!=0)
		{
			response.sendRedirect("/Price/index.jsp");
			return;
		}
		else{
			out.print("创建失败");
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
