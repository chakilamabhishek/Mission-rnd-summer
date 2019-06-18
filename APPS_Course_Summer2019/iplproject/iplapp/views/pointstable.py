from django.db.models import Count
from django.shortcuts import render
from iplapp.models import *
from django.views import View


def pointsdata(year):
    total_teams = Matches.objects.filter(season=year).values('team1').distinct().count()
    matches = Matches.objects.filter(season=year).values_list('winner').annotate(won=Count('winner')).order_by(
        '-won')
    my_dict = []
    for i in range(1, total_teams + 1):
        temp = []
        temp.append(i)
        temp.append(matches[i - 1][0])
        temp.append((total_teams - 1) * 2)
        temp.append(matches[i - 1][1])
        temp.append(((total_teams - 1) * 2) - matches[i - 1][1])
        my_dict.append(temp)
    return my_dict


def getTeamStats(team):
    seasonStats = []
    for year in range(2008,2020):
        temp = pointsdata(year)
        for row in temp:
            if(row[1]==team):
                row.pop(1)
                row.insert(0,year)
                if(row[1]==1):
                    row.append("champion")
                elif(row[1]==2):
                    row.append("Runner up")
                elif (row[1]==3 or row[1]==4 ):
                    row.append('reached playoffs but lost in leauge')
                else:
                    row.append("not reached playoffs")
                seasonStats.append(row)
    return seasonStats


class Points(View):
    def get(self,request,*args,**kwargs):
        if(kwargs):
            my_dict=pointsdata(kwargs['season'])
            season=kwargs['season']
        else:
            my_dict=pointsdata(2019)
            season=2019
        return render(request, template_name="iplapp/points.html",
                      context={
                          'matches':my_dict,
                          'season':season,
                      })

class Teamhomepage(View):
    def get(self,request,*args,**kwargs):
        if(kwargs):
            teams = {1: 'Royal Challengers Bangalore', 2: 'Mumbai Indians', 3: 'Sunrisers Hyderabad',
                     4: 'Rajasthan Royals',
                     5: 'Delhi Capitals',
                     6: 'Kings XI Punjab', 7: 'Chennai Super Kings', 8: 'Gujarat Lions', 9: 'Rising Pune Supergiant',
                     10: 'Pune Warriors', 11: 'Kolkata Knight Riders',
                     12: 'Kochi Tuskers Kerala', 13: 'Deccan Chargers', 14: 'Delhi Daredevils'}
            seasonStats = getTeamStats(teams[kwargs['season']])
            print(teams)
            print(seasonStats)
            return render(request,
                          template_name="iplapp/teamhomepage.html",
                          context={'stats': seasonStats, 'team': teams[kwargs['season']] ,'user': request.user,},
                          )