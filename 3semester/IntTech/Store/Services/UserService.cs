using Microsoft.Extensions.Options;
using Mocassini.Helpers;
using Mocassini.Helpers.Authorization;
using Mocassini.Helpers.Helpers;
using Mocassini.Helpers.Models;
using Mocassini.Models.DTO;

namespace Mocassini.Services;

public interface IUserService
{
    AuthenticateResponse Authenticate(AuthenticateRequest model);
    IEnumerable<UserEntity> GetAll();
    UserEntity GetById(int id);
}

public class UserService : IUserService
{
    private AppDbContext _context;
    private IJwtUtils _jwtUtils;
    private readonly AppSettings _appSettings;

    public UserService(
        AppDbContext context,
        IJwtUtils jwtUtils,
        IOptions<AppSettings> appSettings)
    {
        _context = context;
        _jwtUtils = jwtUtils;
        _appSettings = appSettings.Value;
    }


    public AuthenticateResponse Authenticate(AuthenticateRequest model)
    {
        var user = _context.Users.SingleOrDefault(x => x.Username == model.Username);

        // validate
        if (user == null || !BCrypt.Net.BCrypt.Verify(model.Password, user.PasswordHash))
            throw new AppException("Username or password is incorrect");

        // authentication successful so generate jwt token
        var jwtToken = _jwtUtils.GenerateJwtToken(user);
        
        Console.WriteLine(jwtToken);

        return new AuthenticateResponse(user, jwtToken);
    }

    public IEnumerable<UserEntity> GetAll()
    {
        return _context.Users;
    }

    public UserEntity GetById(int id) 
    {
        var user = _context.Users.Find(id);
        if (user == null) throw new KeyNotFoundException("User not found");
        return user;
    }
}