## RLS

There are two ways a policy can be applied to a table — as a [permissive] policy or as a [restrictive] policy. Policies are permissive by default.

Each does roughly as you’d expect — permissive policies define the set of records you’re permitted to read, whereas restrictive policies will restrict you from reading a particular record, even if there exists a permissive policy that grants you access to said record.

**You have to have at least one permissive policy to be able to query the table. A table with only restrictive policies will not allow any queries at all.**

Permissive policies are applied using a boolean “OR”, so you only need permission from one permissive policy to be able to query a certain row. Restrictive policies, on the other hand, are applied using a boolean “AND” — you have to pass all restrictive policies for every row you want to be able to read.

> Exerpted from [A Friendly Introduction to RLS Policies in Postgres](https://cord.com/techhub/architecture/articles/a-friendly-introduction-to-rls-policies-in-postgre#:~:text=Permissive%20policies%20are%20applied%20using,to%20be%20able%20to%20read.)

## Auth

### Session

Supbase uses [JWT](https://supabase.com/docs/guides/auth/jwts) together with session table.



The reason to use JWT is to have the benifits listed in [What are the benefits of using access and refresh tokens instead of traditional sessions?](https://supabase.com/docs/guides/auth/sessions#what-are-the-benefits-of-using-access-and-refresh-tokens-instead-of-traditional-sessions)

When a user authenticates with Supabase Auth, two pieces of information are issued by the server:

1. Access token in the form of a JWT.
2. Refresh token which is a randomly generated string.

> [what is the purpose of a refresh token](https://stackoverflow.com/questions/38986005/what-is-the-purpose-of-a-refresh-token)

By default, JWT is designed to be used in brower env, since Next.JS uses server side rendering (SSR), some components run on server can not access local storage cookies, thus JWT.



https://supabase.com/docs/guides/auth/server-side/advanced-guide


What is PKCE? 

HOW SSR works to set the cookies. 

what is code and exchangeAccessToken



