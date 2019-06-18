from django.shortcuts import render, redirect
from iplapp.models import *
from django.urls import resolve
from django.views import View
from django.core.paginator import Paginator


class Summerypage(View):
    def get(self,request,*args,**kwargs):
        if(kwargs):
            matches = Matches.objects.filter(**kwargs).values_list('team1','team2','venue','toss_winner','toss_decision','winner','player_of_match','m_id')

            paginator = Paginator(matches, 8)
            print(matches)
            page = request.GET.get('page')
            matches = paginator.get_page(page)
            return render(request, template_name="iplapp/summerypage.html",
                          context={
                              'matches': matches,
                              'user':request.user,
                              'season':kwargs['season']
                          }
                          )

        else:
            matches = Matches.objects.filter(season=2019).values_list('team1', 'team2', 'venue', 'toss_winner',
                                                                      'toss_decision', 'winner', 'player_of_match','m_id')
            paginator = Paginator(matches, 8)
            print(matches)
            page = request.GET.get('page')
            matches = paginator.get_page(page)
            return render(request, template_name="iplapp/summerypage.html",
                          context={
                              'matches': matches,
                              'user': request.user,
                              'season':2019,
                          }
                          )







