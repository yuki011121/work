package algorithm;

import java.util.*;
import java.math.*;

public class AliasMethod {
	private Vector<BigDecimal> prad = null;
	private Vector<Integer> alias = null;
	private Vector<Integer> numList = null;
	private Vector<Integer> rewardMap = null;
	private Vector<Integer> winnerList = new Vector<Integer>();
	private int totalReward = 0;
	
	public void setNumList(Integer[] tnumList)
	{
		numList = new Vector<Integer>(Arrays.asList(tnumList));
		rewardMap = new Vector<Integer>();
		int i;
		for(i = 0; i < numList.size(); i++)
		{
			totalReward+=numList.get(i);
			rewardMap.add(i);
		}
			
	}
	
	public void init()
	{
		int i;
		int len = numList.size(), totalNum = 0;
		Vector<BigDecimal> tempPrad = new Vector<BigDecimal>(len);
		Queue<Integer> bigger = new LinkedList<Integer>();
		Queue<Integer> smaller = new LinkedList<Integer>();
		
		prad = new Vector<BigDecimal>();
		alias = new Vector<Integer>();
		
		//System.out.println(alias.size());
		
		for(i = 0; i < len; i++)
		{
			totalNum += numList.get(i);
			alias.add(i);
			prad.add(new BigDecimal("0"));
			tempPrad.add(new BigDecimal("0.0"));
		}
		
		if(totalNum == 0)
			return;
		
		BigDecimal tempTotalNum = new BigDecimal(Double.toString(totalNum));
		for(i = 0; i < len; i++)
		{

			prad.set(i, (new BigDecimal(Double.toString(numList.get(i)))).divide(
					tempTotalNum, 10, BigDecimal.ROUND_HALF_DOWN));
			tempPrad.set(i, prad.get(i).multiply(new BigDecimal(Double.toString(len))));
			if(tempPrad.get(i).compareTo(new BigDecimal("1.00002")) > 0)
				bigger.offer(i);
			else if(tempPrad.get(i).compareTo(new BigDecimal("0.99998")) < 0)
				smaller.offer(i);
		}		
		
		int biggerHead, smallerHead;
		while(!bigger.isEmpty() && !smaller.isEmpty())
		{
			biggerHead = bigger.poll();
			smallerHead = smaller.poll();
			
			tempPrad.set(biggerHead,
					tempPrad.get(biggerHead).add(tempPrad.get(smallerHead).subtract(new BigDecimal("1"))));
			tempPrad.set(smallerHead, new BigDecimal("1.0000000000"));
			alias.setElementAt(biggerHead, smallerHead);
			
			if(tempPrad.get(biggerHead).compareTo(new BigDecimal("1.00002")) > 0)
				bigger.offer(biggerHead);
			else if(tempPrad.get(biggerHead).compareTo(new BigDecimal("0.99998")) < 0)
				smaller.offer(biggerHead);

		}
		
//		if(tempPrad[0].compareTo(new BigDecimal("1.0")) < 0)
//			System.out.println("true");
//		else
//			System.out.println("false");
		
		int fiNum;
		double secNum;
		Random rand = new Random();

		fiNum = rand.nextInt(len);
		secNum = rand.nextDouble();
		if(prad.get(fiNum).compareTo(new BigDecimal(Double.toString(secNum))) > 0)
		{
			numList.setElementAt(numList.get(alias.get(fiNum)) - 1, alias.get(fiNum));
			winnerList.add(rewardMap.get(alias.get(fiNum)));
			if(numList.get(alias.get(fiNum)) == 0)
			{
				numList.remove(alias.get(fiNum));
				rewardMap.remove(alias.get(fiNum));
			}
				
		}
		else
		{
			numList.setElementAt(numList.get(fiNum) - 1, fiNum);
			winnerList.add(rewardMap.get(fiNum));
			if(numList.get(fiNum) == 0)
			{
				numList.remove(fiNum);
				rewardMap.remove(fiNum);
			}
				
		}

	}
	
	public void test()
	{
		
		int i;
		for( i = 1; i <= totalReward; i++)
			init();
//		for( i = 0; i < prad.size(); i++)
//		{
//			System.out.println(i + " " + prad.get(i) + " " + alias.get(i));
//		}
//		
		for( i = 0; i < winnerList.size(); i++)
			System.out.println(winnerList.get(i));
	}
	
	public void run()
	{
		
	}
	
}
