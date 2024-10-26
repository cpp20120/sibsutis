using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Options;
using Mocassini.Helpers.Authorization;
using Mocassini.Helpers.Helpers;
using Mocassini.Helpers.Models;
using Mocassini.Models.DTO;
using Mocassini.Services;

namespace Mocassini.Helpers.Controllers;

[ApiController]
[Route("[controller]")]
public class UserController : Controller
{
    private readonly ILogger<UserController> _logger;
    private readonly AppDbContext _dbContext;
    private readonly IUserService _userService;
    private readonly IJwtUtils _jwtUtils;
    private readonly AppSettings _appSettings;


    public UserController(ILogger<UserController> logger, AppDbContext dbContext,
        IUserService userService, IJwtUtils jwtUtils, IOptions<AppSettings> appSettings
    )
    {
        _logger = logger;
        _dbContext = dbContext;
        _userService = userService;
        _jwtUtils = jwtUtils;
        _appSettings = appSettings.Value;
    }

    [HttpGet(Name = "GetUsers")]
    [Authorization.Authorize(Role.Storekeeper)]
    public IEnumerable<UserEntity> Get()
    {
        return _dbContext.Users;
    }

    [HttpGet("{id}", Name = "GetUser")]
    [Authorization.Authorize(Role.Storekeeper)]
    public UserEntity Get(int id)
    {
        return _dbContext.Users.Find(id);
    }

    [HttpGet("me", Name = "GetMe")]
    [Authorization.Authorize]
    public UserEntity GetMe()
    {
        var user = (UserEntity)HttpContext.Items["User"];
        return user;
    }

    [HttpPost(Name = "CreateUser")]
    [AllowAnonymous]
    public UserEntity Create(
        [FromBody] CreateUserRequest req)
    {
        var user = _dbContext.Users.Add(
            new UserEntity
            {
                Name = req.Name,
                Surname = req.Surname,
                Username = req.Username,
                PasswordHash = BCrypt.Net.BCrypt.HashPassword(req.Password),
            }
        );

        _dbContext.SaveChanges();
        return user.Entity;
    }

    [HttpDelete("{id}", Name = "DeleteUser")]
    [Authorization.Authorize(Role.Storekeeper)]
    public void Delete(int id)
    {
        var user = _dbContext.Users.Find(id);
        _dbContext.Users.Remove(user);
        _dbContext.SaveChanges();
    }
    
    [HttpPost("authenticate", Name = "Authenticate")]
    [AllowAnonymous]
    public AuthenticateResponse Authenticate(
        [FromBody] AuthenticateRequest req
    )
    {
        var response = _userService.Authenticate(req);
        
        // log response
        _logger.LogInformation("User {Username} authenticated, {response}", req.Username, response.Token);

        return response;
    }
}