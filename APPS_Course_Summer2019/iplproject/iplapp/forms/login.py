from django import forms


class LoginForm(forms.Form):
    user = forms.CharField(
        required=True,
        widget= forms.TextInput(
            attrs={'class': 'input', 'placeholder': 'enter name', 'name': 'user' })
    )
    password = forms.CharField(
        required=True,
        widget=forms.PasswordInput(attrs={'class': 'input', 'placeholder': 'enter password', 'name': 'password' })
    )