package algorithm;

import java.math.BigDecimal;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;
import java.util.Vector;

public class Improve {
	private Vector<Integer> numList = null;
	private Vector<Integer> rewardMap = null;
	private Vector<Integer> winnerList = new Vector<Integer>();
	private int totalReward = 0;
	private double[] prad = null;
	private int totalNum = 0;
	
	public void setNumList(Integer[] tnumList)
	{
		numList = new Vector<Integer>(Arrays.asList(tnumList));
		rewardMap = new Vector<Integer>();
		int i;
		for(i = 0; i < numList.size(); i++)
		{
			totalReward+=numList.get(i);
			rewardMap.add(i);
			totalNum += numList.get(i);
		}
			
	}
	
	public void init()
	{
		int i;
		int len = numList.size();
		double maxPrad = -1;
		totalNum = 0;
		
		prad = new double[len];
		for(i = 0; i < len; i++)
			totalNum += numList.get(i);
		
		if(totalNum == 0)
			return;
		
		for(i = 0; i < len; i++)
		{
			prad[i] = (double)numList.get(i) / totalNum;
			if(maxPrad < prad[i])
				maxPrad = prad[i];
		}
		
		for(i = 0; i < len; i++)
			prad[i] /= maxPrad;
		
		int fiNum;	
		double secNum;
		Random rand = new Random();

		fiNum = rand.nextInt(len);
		secNum = rand.nextDouble();
		if(secNum <= prad[fiNum])
		{

			numList.setElementAt(numList.get(fiNum) - 1, fiNum);
			winnerList.add(rewardMap.get(fiNum));
			if(numList.get(fiNum) == 0)
			{
				numList.remove(fiNum);
				rewardMap.remove(fiNum);
			}

		}
		else
			winnerList.add(-1);

	}
	
	public void test()
	{
		
		int i;
		while(totalNum > 0)
			init();
		for( i = 0; i < winnerList.size(); i++)
			System.out.println(winnerList.get(i));
	}
}
