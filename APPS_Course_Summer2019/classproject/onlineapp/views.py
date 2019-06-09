from django.shortcuts import render

# Create your views her
from onlineapp import models
from django.http import HttpResponse
from django.http import HttpRequest


def hello(request):
    # val=request.headers['Foo']
    Col=models.College.objects.values_list('name').get(acronym='cmr')
    text = """<h1>hello !</h1>"""
    return HttpResponse(Col)


def getallcolleges(request):
    # val=request.headers['Foo']
    Col=models.College.objects.values_list('name','acronym')
    text = """<body>
               <table border=1>"""
    for x in Col:
        text+="<tr><td>"+x[0]+"</td><td>"+x[1]+"</td></tr>"
    text+="</table>"
    return HttpResponse(text)

#
#     return render(request,'onlineapp/mycollegedata.html',context={'my_dict':my_dict})
#
# my_dict =models.College.objects.values('name','acronym')
def getallclglinks(request):
    my_dict=models.College.objects.values('id','name','acronym')
    return render(request,'onlineapp/mycollegelinks.html',context={'my_dict':my_dict})
def getallclgtemplates(request,id):
    my_dict =models.Student.objects.values('name','email','mocktest1__total','college__name','college').filter(college=id)
    print(my_dict)
    return render(request,'onlineapp/mycollegedata.html',context={'my_dict':my_dict})