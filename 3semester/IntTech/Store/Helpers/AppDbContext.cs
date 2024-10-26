using System.Text.Json;
using Microsoft.EntityFrameworkCore;
using Mocassini.Helpers.Models;

namespace Mocassini.Helpers;

public class AppDbContext : DbContext
{
    public DbSet<BrandEntity> Brands { get; set; } = null!;
    public DbSet<ShoeEntity> Shoes { get; set; } = null!;
    public DbSet<ShoeSizeEntity> ShoeSizes { get; set; } = null!;
    public DbSet<UserEntity> Users { get; set; } = null!;
    public DbSet<OrderEntity> Orders { get; set; } = null!;
    public DbSet<OrderItemEntity> OrderItems { get; set; } = null!;

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<ShoeEntity>()
            .HasOne(s => s.Brand)
            .WithMany(b => b.Shoes)
            .HasForeignKey(s => s.BrandId)
            .OnDelete(DeleteBehavior.Cascade);

        modelBuilder.Entity<OrderItemEntity>()
            .HasOne(oi => oi.ShoeSize)
            .WithMany(si => si.OrderItems)
            .HasForeignKey(oi => oi.ShoeSizeId)
            .OnDelete(DeleteBehavior.Cascade);

        modelBuilder.Entity<OrderItemEntity>()
            .HasOne(oi => oi.Order)
            .WithMany(o => o.Items)
            .HasForeignKey(oi => oi.OrderId)
            .OnDelete(DeleteBehavior.Cascade);

        modelBuilder.Entity<OrderEntity>()
            .HasOne(o => o.User)
            .WithMany(u => u.Orders)
            .HasForeignKey(o => o.UserId)
            .OnDelete(DeleteBehavior.Cascade);
        
        modelBuilder.Entity<OrderItemEntity>()
            .HasOne(oi => oi.ShoeSize)
            .WithMany(si => si.OrderItems)
            .HasForeignKey(oi => oi.ShoeSizeId);

        modelBuilder.Entity<OrderEntity>()
            .Property(o => o.Address)
            .HasConversion(
                a => JsonSerializer.Serialize(a,
                    new JsonSerializerOptions { IgnoreNullValues = true }
                ),
                a => JsonSerializer.Deserialize<AddressVO>(a,
                    new JsonSerializerOptions { IgnoreNullValues = true }
                )
            );

        modelBuilder.Entity<OrderEntity>()
            .HasOne(o => o.User)
            .WithMany(u => u.Orders)
            .HasForeignKey(o => o.UserId);

        modelBuilder.Entity<UserEntity>()
            .HasIndex(u => u.Username)
            .IsUnique();
    }

    public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
    {
    }
}