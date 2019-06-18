from django.db.models import Count, Sum
from django.shortcuts import render, redirect
from iplapp.models import *
from django.urls import resolve
from django.views import View
from django.contrib.auth.mixins import LoginRequiredMixin


class Matchdetails(LoginRequiredMixin,View):
    login_url = '/login/'
    def get(self,request,*args,**kwargs):
        print(kwargs)
        if(kwargs):
            matches = Matches.objects.filter(m_id=kwargs['match']).values_list('team1', 'team2','venue','toss_winner',
                                                                   'toss_decision', 'winner', 'player_of_match', 'm_id')
            deliveries=[]
            deliveries.append(Deliveries.objects.filter(**kwargs,inning=1).values_list().values_list('inning','over','ball','batsman','bowler','total_runs','batsman_runs','player_dismissed','dismissal_kind','fielder'))
            deliveries.append(
                Deliveries.objects.filter(**kwargs,inning=2).values_list().values_list('inning', 'over', 'ball', 'batsman',
                                                                              'bowler', 'total_runs', 'batsman_runs',
                                                                              'player_dismissed', 'dismissal_kind',
                                                                              'fielder'))
            top3_scorers = Deliveries.objects.values('batsman').filter(**kwargs,inning=1).annotate(sum=Sum('total_runs')).order_by('-sum')[0:3]
            top3_wicket_takers = Deliveries.objects.values('bowler','fielder').filter(**kwargs,inning=1).exclude(fielder='').annotate(count=Count('fielder')).order_by('-count')[0:3]
            top3_scorers1= Deliveries.objects.values('batsman').filter(**kwargs, inning=2).annotate(
                sum=Sum('total_runs')).order_by('-sum')[0:3]
            top3_wicket_takers1 = Deliveries.objects.values('bowler', 'fielder').filter(**kwargs, inning=2).exclude(
                fielder='').annotate(count=Count('fielder')).order_by('-count')[0:3]
            stats=[]
            stats1=[]
            print(top3_wicket_takers)
            for i in range(3):
                temp=[]
                temp.append(i+1)
                temp.append(top3_scorers[i]['batsman'])
                temp.append(top3_scorers[i]['sum'])
                temp.append(top3_wicket_takers[i]['fielder'])
                temp.append(top3_wicket_takers[i]['count'])

                stats.append(temp)
            for i in range(3):
                temp=[]
                temp.append(i+1)
                temp.append(top3_scorers1[i]['batsman'])
                temp.append(top3_scorers1[i]['sum'])
                temp.append(top3_wicket_takers1[i]['fielder'])
                temp.append(top3_wicket_takers1[i]['count'])

                stats1.append(temp)

            print(deliveries)
            return render(request, template_name="iplapp/matchdetails.html",
                          context={
                              'my_dict': matches,
                              'deliveries':deliveries,
                              'stats':stats,
                              'stats1':stats1,
                          }
                          )
