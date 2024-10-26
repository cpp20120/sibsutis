using Microsoft.AspNetCore.Mvc;
using Mocassini.Helpers.Authorization;
using Mocassini.Helpers.Helpers;
using Mocassini.Helpers.Models;

namespace Mocassini.Helpers.Controllers;

[ApiController]
[Route("[controller]")]
public class OrderController : Controller
{
    AppDbContext _dbContext;
    ILogger<OrderController> _logger;

    public OrderController(AppDbContext dbContext,
        ILogger<OrderController> logger)
    {
        _dbContext = dbContext;
        _logger = logger;
    }

    public class CreateOrderRequestItem
    {
        public int ShoeSizeId { get; set; }
        public int Quantity { get; set; }
    }

    public class CreateOrderRequest
    {
        public IEnumerable<CreateOrderRequestItem> Items { get; set; }
        public AddressVO Address { get; set; } = null!;
        public string? Comment { get; set; }
    }

    [HttpPost(Name = "CreateOrder")]
    public void Create([FromBody] CreateOrderRequest req)
    {
        var user = (UserEntity)HttpContext.Items["User"];
        var order = new OrderEntity
        {
            Address = req.Address,
            UserId = user.Id,
            Comment = req.Comment,
            Items = req.Items.Select(
                i => new OrderItemEntity
                {
                    ShoeSizeId = i.ShoeSizeId,
                    Quantity = i.Quantity
                }
            ).ToList()
        };

        foreach (var item in order.Items)
        {
            var shoeSize = _dbContext.ShoeSizes.Find(item.ShoeSizeId);
            shoeSize.Quantity -= item.Quantity;
        }

        _dbContext.Orders.Add(order);
        _dbContext.SaveChanges();
    }

    [HttpGet(Name = "GetMyOrders")]
    public IEnumerable<OrderEntity> GetMyOrders()
    {
        var user = (UserEntity)HttpContext.Items["User"];
        return _dbContext.Orders.Where(o => o.UserId == user.Id).Select(
            o => new OrderEntity
            {
                Id = o.Id,
                Address = o.Address,
                Status = o.Status,
                Comment = o.Comment,
                TrackingNumber = o.TrackingNumber,
                CreatedAt = o.CreatedAt,
                Items = o.Items.Select(
                    i => new OrderItemEntity
                    {
                        Id = i.Id,
                        Quantity = i.Quantity,
                        ShoeSize = new ShoeSizeEntity
                        {
                            Id = i.ShoeSize.Id,
                            Size = i.ShoeSize.Size,
                            Shoe = new ShoeEntity
                            {
                                Id = i.ShoeSize.Shoe.Id,
                                Name = i.ShoeSize.Shoe.Name,
                                Brand = new BrandEntity
                                {
                                    Id = i.ShoeSize.Shoe.Brand.Id,
                                    Name = i.ShoeSize.Shoe.Brand.Name,
                                    Description = i.ShoeSize.Shoe.Brand.Description,
                                    ExternalLogoId = i.ShoeSize.Shoe.Brand.ExternalLogoId
                                },
                                Description = i.ShoeSize.Shoe.Description,
                                Price = i.ShoeSize.Shoe.Price,
                                ImagesURLs = i.ShoeSize.Shoe.ImagesURLs
                            }
                        }
                    }
                )
            }
        ).OrderByDescending(
            o => o.CreatedAt
        );
    }
    
    // get all orders for admin:
    [HttpGet("all", Name = "GetAllOrders")]
    [Authorize(Role.Storekeeper)]
    public IEnumerable<OrderEntity> GetAllOrders()
    {
        return _dbContext.Orders.Select(
            o => new OrderEntity
            {
                Id = o.Id,
                Address = o.Address,
                Status = o.Status,
                Comment = o.Comment,
                TrackingNumber = o.TrackingNumber,
                CreatedAt = o.CreatedAt,
                Items = o.Items.Select(
                    i => new OrderItemEntity
                    {
                        Id = i.Id,
                        Quantity = i.Quantity,
                        ShoeSize = new ShoeSizeEntity
                        {
                            Id = i.ShoeSize.Id,
                            Size = i.ShoeSize.Size,
                            Shoe = new ShoeEntity
                            {
                                Id = i.ShoeSize.Shoe.Id,
                                Name = i.ShoeSize.Shoe.Name,
                                Brand = new BrandEntity
                                {
                                    Id = i.ShoeSize.Shoe.Brand.Id,
                                    Name = i.ShoeSize.Shoe.Brand.Name,
                                    Description = i.ShoeSize.Shoe.Brand.Description,
                                    ExternalLogoId = i.ShoeSize.Shoe.Brand.ExternalLogoId
                                },
                                Description = i.ShoeSize.Shoe.Description,
                                Price = i.ShoeSize.Shoe.Price,
                                ImagesURLs = i.ShoeSize.Shoe.ImagesURLs
                            }
                        }
                    }
                )
            }
        ).OrderByDescending(
            o => o.CreatedAt
        );
    }
    
    // patch order for admin
    public class PatchOrderRequest
    {
        public OrderStatus Status { get; set; }
        public string? TrackingNumber { get; set; }
    }
    
    [HttpPatch("{id}", Name = "PatchOrder")]
    [Authorize(Role.Storekeeper)]
    public void Patch(int id, [FromBody] PatchOrderRequest req)
    {
        var order = _dbContext.Orders.Find(id);
        if (order == null)
        {
            throw new AppException("Order not found");
        }

        order.Status = req.Status;
        order.TrackingNumber = req.TrackingNumber;
        _dbContext.SaveChanges();
    }
}