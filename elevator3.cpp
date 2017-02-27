#include<bits/stdc++.h>
//roughdraft
using namespace std;

long long int n=0;
long long int maxfloors=20;//bouncing is allowed due to this

int requests[20];
int downel[20];
int upel[20];
class elevator
{	
private:
	int elevatornumber;
	int curfloor;
	int goalfloor;
public:

	int stops[20];
	static long long int count;
	elevator()
	{
		curfloor=0;
		elevatornumber=count;
		count++;
		int i;
		for(i=0;i<maxfloors;i++)
		{
			stops[maxfloors]=0;
		}
	}
	int getfloor()
	{
		return curfloor;
	}
	elevator(int f)
	{	
		curfloor=f;
		elevatornumber=count;
		count++;
	}
	
	int getelevatornumber()
	{
		return elevatornumber;
	}
	int getcurfloor()
	{
		return curfloor;
	}
	
	int getgoalfloor()
	{
		return goalfloor;
	}

	int setcurfloor(int f)
	{
		curfloor=f;
	}
	int setgoalfloor(int f)
	{
		goalfloor=f;
	}


};
long long int elevator::count=0;
long long int f=1;
long long int c=10;



elevator elv[20];


void status()
{
	printf("n=%lld\n",n);
	int i;
	for(i=0;i<n;i++)
	{
		printf("(%d, %d, %d)\n",elv[i].getelevatornumber(), elv[i].getcurfloor(), elv[i].getgoalfloor());
	}
}


void setgoal(int elvid,int goalf) //person requesting to go some floor
{
	elv[elvid].stops[goalf]=1;
}

void update(int elvid, int curfloor, int goalfoor)
{
	elv[elvid].setgoalfloor(goalfoor);
	elv[elvid].setcurfloor(curfloor);

}

void pickup(int floor, int dir)
{

	//0 = no request
	//1 = down
	//2 = up
	//3 = both
	if(requests[floor]==0)
	{
		if(dir<0)
			requests[floor]=1;
		else
			requests[floor]=2;
	}
	else
	{
		if(requests[floor]==1)
		{
			if(dir>0)
				requests[floor]=3;
		}
		else if(requests[floor]==2)
		{
			if(dir<0)
				requests[floor]=3;
		}
		else if(requests[floor]=3)
		{
			//do nothing.
		}
	}

}

void chooseup(int r)
{
	int i;
	int w=0;
	int chooseelv=-1;

	int timetowait=0;
	int electricity=0;
	int costtoreach=0;
	int globalmin = 10*maxfloors+1; 

	for(i=0;i<n;i++)
	{
		if(elv[i].getcurfloor() <= r) //below it
		{
			if(elv[i].getgoalfloor()>elv[i].getcurfloor()) //coming up towards it.
			{
				timetowait= abs(r- elv[i].getcurfloor());

				if(elv[i].getgoalfloor()>=r)
					electricity=0;
				else
					electricity=r-elv[i].getgoalfloor();

				costtoreach=timetowait+electricity;
				if(costtoreach<globalmin)
				{					
					globalmin = costtoreach;
					chooseelv= i;
				}

			}
			else //is down and going down
			{
				timetowait = abs(elv[i].getgoalfloor() -elv[i].getcurfloor()) + abs(r-elv[i].getgoalfloor());
				int j;

				electricity = abs(r- elv[i].getgoalfloor());
				costtoreach=timetowait+electricity;
				if(costtoreach<globalmin)
				{					
					globalmin = costtoreach;
					chooseelv= i;
				}

			}
		}
		else //above it
		{
			if(elv[i].getgoalfloor()>elv[i].getcurfloor()) //going further up
			{
				timetowait= abs(elv[i].getgoalfloor()-r) + abs(elv[i].getgoalfloor()-elv[i].getcurfloor());
				electricity=abs(elv[i].getgoalfloor()-r);
				costtoreach=timetowait+electricity;

				if(costtoreach<globalmin)
				{					
					globalmin = costtoreach;
					chooseelv= i;
				}

			}
			else //coming down
			{
				timetowait = abs(elv[i].getcurfloor() -elv[i].getgoalfloor()) + abs(elv[i].getgoalfloor()-r);
				
				if(elv[i].getgoalfloor()>r)
					electricity = abs(elv[i].getgoalfloor()-r);
				else
					electricity = 0;
					
				
					costtoreach=timetowait+electricity;
					if(costtoreach<globalmin)
					{					
						globalmin = costtoreach;
						chooseelv= i;
					}

			}
		}


	}

	elv[chooseelv].stops[r]=1;
	//printf("chosen elv:%d for up at floor: %d\n",chooseelv,r);

}




void choosedown(int r)
{
	int i;
	int w=0;
	int chooseelv=-1;

	int timetowait=0;
	int electricity=0;
	int costtoreach=0;
	int globalmin = 10*maxfloors+1; 

	for(i=0;i<n;i++)
	{
		if(elv[i].getcurfloor() <= r) //below it
		{
			if(elv[i].getgoalfloor()>elv[i].getcurfloor()) //coming up towards it.
			{
				timetowait= abs(r- elv[i].getgoalfloor()) +abs(elv[i].getgoalfloor()-elv[i].getcurfloor());

				if(elv[i].getgoalfloor()>=r)
					electricity=0;
				else
					electricity=abs(r-elv[i].getgoalfloor());

				costtoreach=timetowait+electricity;
				if(costtoreach<globalmin)
				{					
					globalmin = costtoreach;
					chooseelv= i;
				}

			}
			else //is down and going down
			{
				timetowait = abs(elv[i].getgoalfloor() -elv[i].getcurfloor()) + abs(r-elv[i].getgoalfloor());
				int j;

				electricity = abs(r- elv[i].getgoalfloor());
				costtoreach=timetowait+electricity;
				if(costtoreach<globalmin)
				{					
					globalmin = costtoreach;
					chooseelv= i;
				}

			}
		}
		else //above it
		{
			if(elv[i].getgoalfloor()>elv[i].getcurfloor()) //going further up
			{
				timetowait= abs(elv[i].getgoalfloor()-r) + abs(elv[i].getgoalfloor()-elv[i].getcurfloor());
				electricity=abs(elv[i].getgoalfloor()-r);
				costtoreach=timetowait+electricity;

				if(costtoreach<globalmin)
				{					
					globalmin = costtoreach;
					chooseelv= i;
				}

			}
			else //coming down
			{
				timetowait = abs(elv[i].getcurfloor() -r);
				
				if(elv[i].getgoalfloor()>r)
					electricity = abs(elv[i].getgoalfloor()-r);
				else
					electricity = 0;
					
				
					costtoreach=timetowait+electricity;
					if(costtoreach<globalmin)
					{					
						globalmin = costtoreach;
						chooseelv= i;
					}

			}
		}


	}

	elv[chooseelv].stops[r]=1;
	//printf("chosen elv:%d for down at floor: %d\n",chooseelv,r);

}





void servicerequest(int r)
{
	//from all elevators coming in its direction, choose closest
	if(requests[r]==1)
	{
		choosedown(r);

	}
	else if(requests[r]==2)
	{
		chooseup(r);

	}
	else
	{
		chooseup(r);
		choosedown(r);
	}
	requests[r]=0;

	//if no elevator in this direction, choose one that takes least time to get to it after completing that directions goal state
}

void moveelevator(int el)
{

	//printf("Moving elevator: %d right now at: %d with goal: %d\n",el,elv[el].getcurfloor(),elv[el].getgoalfloor());
	if(elv[el].getcurfloor()>elv[el].getgoalfloor())
	{
		//	printf("going down\n");
		
		int j=0;
		int newgoal = elv[el].getgoalfloor();
		for(j=0;j<=elv[el].getgoalfloor();j++)
		{
			if(elv[el].stops[j]==1)
			{
				newgoal=j;
			}
		}
		update(el,elv[el].getcurfloor()-1,newgoal);
		//printf("Now elevator: %d stepping at: %d with goal: %d\n",el,elv[el].getcurfloor(),elv[el].getgoalfloor());

	}
	else if(elv[el].getcurfloor()<elv[el].getgoalfloor())
	{
		//printf("going down\n");
		int j=maxfloors;
		int newgoal = elv[el].getgoalfloor();
		for(j=maxfloors;j>=elv[el].getgoalfloor();j--)
		{
			if(elv[el].stops[j]==1)
			{
				newgoal=j;
			}
		}
		update(el,elv[el].getcurfloor()+1,newgoal);
		//printf("Now elevator: %d stepping at: %d with goal: %d\n",el,elv[el].getcurfloor(),elv[el].getgoalfloor());

	}
	else
	{
		//printf("finding new goal\n");
		int minstop=maxfloors+1;
		int maxstop=-1;
		int j=0;
		int newgoal = elv[el].getgoalfloor();
		for(j=0;j<maxfloors;j++)
		{
			if(elv[el].stops[j]==1)
			{
				if(j>maxstop)
					maxstop=j;
				if(j<minstop)
					minstop=j;
			}
		}
		//printf("gotten: minstop=%d, maxtop=%d\n",minstop,maxstop);
		if(minstop == maxfloors+1)
		{
			//do nothing 
			//printf("just staying here\n");
			return;
		}
		if(minstop < elv[el].getcurfloor())
		{
			update(el,elv[el].getcurfloor()-1,minstop);
			return;
		}
		else if(minstop > elv[el].getcurfloor())
		{
			update(el,elv[el].getcurfloor()+1,maxstop);
			return;
		}
		else
		{
			elv[el].stops[j]=0;
			update(el,elv[el].getcurfloor(),elv[el].getcurfloor());
			return;
		}

	}

}
void moveelevators()
{
	int i=0;
	for(i=0;i<n;i++)
	{
		moveelevator(i);
	}
}
void step()
{
	int i=0;
	//drop off current passengers
	for(i=0;i<n;i++)
	{
		elv[i].stops[elv[i].getcurfloor()]=0;
	}
	//printf("dropping off done\n");
	//service requests (Assign elevators)
	for(i=0;i<maxfloors;i++)
	{
		if(requests[i]!=0)
		{
			servicerequest(i);			
		}
	}

	moveelevators();
	


}

int main()
{

	int i;
	scanf("%lld\n",&n);
	for(i=0;i<maxfloors;i++)
	{
		requests[i]=0;
		downel[i]=-1;
		upel[i]=-1;
	}
	char delim=' ';
	string line;	
	while(true)
	{
		getline(cin,line);
		stringstream ss;
    	ss.str(line);
    	string item;
    	vector<string> elems;
    	while (getline(ss, item, delim)) 
    	{
        	elems.push_back(item);
    	}
    	if(elems[0]=="pickup")
    	{
    		if(elems.size()==3)
	    		pickup(atoi(elems[1].c_str()),atoi(elems[2].c_str()));

    	}
    	else if(elems[0]=="status")
    	{
    		status();
    	}
    	else if(elems[0]=="update")
    	{
    		if(elems.size()==4)			
 		   		update(atoi(elems[1].c_str()),atoi(elems[2].c_str()),atoi(elems[3].c_str()));
    	}
    	else if(elems[0]=="step")
    	{
    		step();
    	}
    	else if(elems[0]=="goto")
    	{
    		setgoal(atoi(elems[1].c_str()),atoi(elems[2].c_str()));
    	}
    	else
    	{

    		//do nothing;
    	}
	}

	return 0;
}