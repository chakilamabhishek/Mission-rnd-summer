from django.shortcuts import render
from django.urls import resolve
from django.views import View

class Homepage(View):
    def get(self,request):
        return render(request, template_name="iplapp/iplhomepage.html",)

