from django.urls import path,re_path
from . import views

urlpatterns = [
    path('hello/', views.hello, name='hello'),
    path('get_all_colleges/', views.getallcolleges,name='get_all_colleges'),
    path('get_all_colleges_links/', views.getallclglinks, name='get_all_colleges_links'),
    path('get_all_colleges_temp/<int:id>/', views.getallclgtemplates, name='get_all_colleges_temp'),

]
