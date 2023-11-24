package admainPack;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.Vector;
import entity.Admain;

public class ReadU {

	static Vector<Admain> usersList=new Vector<Admain>();
	
	public  Vector<Admain> readusers(String now_path,int pid){
		String No=Integer.toString(pid);
		String filename=No+"User.txt";
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(now_path+"FileUpload/"+filename),"gbk"));
			String data = null; 
			data = br.readLine();
			while((data = br.readLine())!=null) 
			{ 
				String[] ps  =data.split(",");
				String name=ps[0];
				String id=ps[1];
				int llevel =Integer.parseInt(ps[2]);
				String email=ps[3];
				int status=Integer.parseInt(ps[4]);
				

				//
				String  date=ps[5];
				String[] ps1=date.split("/");
				int year=Integer.parseInt(ps1[0]),
						month=Integer.parseInt(ps1[1]);
				String[] ps2=ps1[2].split(" ");
				int date1=Integer.parseInt(ps2[0]);
				String time=ps2[1];
				String[] ps3=ps2[1].split(":");
				int hour=Integer.parseInt(ps3[0]),min=Integer.parseInt(ps3[1]);
				java.util.Date reg_date=new java.util.Date(year,month,date1,hour,min);
				//都只为了获得reg_date
				
				String pass=ps[6];
				
				//System.out.println(email);
				Admain aitem= new Admain();
				aitem.setEmail(email);
				//aitem.setGeo_point(geo_point);
				aitem.setId(id);
				aitem.setLevel(llevel);
				aitem.setName(name);
				aitem.setPass(pass);
				aitem.setReg_date(reg_date);
				aitem.setStatus(status);
				usersList.add(aitem);
			} 
			br.close();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return usersList;
	}
}
