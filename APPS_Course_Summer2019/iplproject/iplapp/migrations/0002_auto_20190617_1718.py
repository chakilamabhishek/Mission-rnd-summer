# Generated by Django 2.2.1 on 2019-06-17 11:48

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('iplapp', '0001_initial'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='matches',
            name='id',
        ),
        migrations.AlterField(
            model_name='matches',
            name='m_id',
            field=models.IntegerField(primary_key=True, serialize=False),
        ),
    ]
