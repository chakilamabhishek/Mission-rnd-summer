from django.urls import path,re_path
from iplapp.views import *

urlpatterns = [
    path('home/', Summerypage.as_view(), name='summerypage'),
    path('home/<int:season>/', Summerypage.as_view(), name='summerypage'),
    path('matchdetails/<int:match>/',Matchdetails.as_view(),name="matchdetails"),
    path('points/', Points.as_view(), name="pointstable"),
    path('points/<int:season>/', Points.as_view(), name="pointstable"),
    path('teamhomepage/<int:season>/', Teamhomepage.as_view(), name="teamhomepage"),
    path('',Homepage.as_view(),name="homepage"),
    path('login/', LoginController.as_view(), name='login'),
    path('signup/', SignupController.as_view(), name='signup'),
    path('logout/', logout_user, name='logout'),
]