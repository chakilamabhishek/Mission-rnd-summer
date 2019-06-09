from django.db import models


class tdlist(models.Model):
    name = models.CharField(max_length=128)
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.name





class tditem(models.Model):
    description = models.CharField(max_length=128)
    due_date = models.DateField(blank=True,null=True)
    completed = models.BooleanField()
    todolist = models.ForeignKey(tdlist, on_delete=models.CASCADE)

    def __str__(self):
        return self.description
