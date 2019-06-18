from django import forms


class SignupForm(forms.Form):
    first_name=forms.CharField(
        required=True,
        widget=forms.TextInput(attrs={'class':'input','placeholder': 'enter first name', })
    )
    last_name = forms.CharField(
        required=True,
        widget=forms.TextInput(attrs={'class': 'input', 'placeholder': 'enter last name', })
    )
    username = forms.CharField(
        required=True,
        widget=forms.TextInput(
            attrs={'class': 'input', 'placeholder': 'enter name',})
    )
    password = forms.CharField(
        required=True,
        widget=forms.PasswordInput(attrs={'class': 'input', 'placeholder': 'enter password', })
    )
