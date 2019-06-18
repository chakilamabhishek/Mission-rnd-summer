from django.shortcuts import render, redirect
from django.views import View
from iplapp.forms import *
from django.contrib.auth.models import User


from django.contrib.auth import authenticate,login,logout
from django.contrib import messages

def logout_user(request):
    logout(request)
    return redirect('/login/')

class LoginController(View):
    def get(self,request):
        if request.user.is_authenticated:
            return redirect('/home/')

        form=LoginForm()
        return render(request,template_name='iplapp/login.html',context={'form':form})

    def post(self,request):
        form=LoginForm(request.POST)
        if form.is_valid():
            username = form.cleaned_data['user']
            password = form.cleaned_data['password']
            print(username,password)
            user = authenticate(request, username=username, password=password)
            print(user)
            if user is not None:
                login(request,user)
                return redirect('/home/')
            else:
                messages.error(request,'invalid credentials')
        return redirect('http://127.0.0.1:8000/login/')


class SignupController(View):
    def get(self,request):
        form=SignupForm()
        return render(request,template_name='iplapp/signup.html',context={'form':form})

    def post(self,request):
        form=SignupForm(request.POST)
        if form.is_valid():
            user=User.objects.create_user(**form.cleaned_data)
            user.save()
            if user is not None:
                login(request,user)
                return redirect('http://127.0.0.1:8000/home/')
            else:
                messages.error(request,'invalid credentials')
        else:
            return render(request, template_name='/signup.html', context={'form': form})